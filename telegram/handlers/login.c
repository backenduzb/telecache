#include "./login.h"
#include <gtk/gtk.h>
#include <glib.h>
#include <td/telegram/td_json_client.h>
#include "../../include/envloader.h"

static void switch_to_phone_ui(LoginContext *ctx)
{
    ctx->stage = STAGE_PHONE;

    gtk_label_set_text(GTK_LABEL(ctx->title), "Enter Phone Number");
    gtk_label_set_text(
        GTK_LABEL(ctx->caption),
        "Please enter your Telegram phone number."
    );

    gtk_entry_set_visibility(GTK_ENTRY(ctx->phone_input), TRUE);

    gtk_editable_set_text(GTK_EDITABLE(ctx->phone_input), "");

    gtk_entry_set_placeholder_text(
        GTK_ENTRY(ctx->phone_input),
        "Phone number"
    );

    gtk_entry_set_max_length(GTK_ENTRY(ctx->phone_input), 20);
}

static void switch_to_sms_ui(LoginContext *ctx)
{
    ctx->stage = STAGE_SMS;

    gtk_box_remove(GTK_BOX(ctx->inputs_con), ctx->reg_input);

    gtk_label_set_text(GTK_LABEL(ctx->title), "Enter SMS Code");
    gtk_label_set_text(
        GTK_LABEL(ctx->caption),
        "Telegram sent you a login code."
    );

    gtk_editable_set_text(GTK_EDITABLE(ctx->phone_input), "");

    gtk_entry_set_placeholder_text(
        GTK_ENTRY(ctx->phone_input),
        "Code"
    );

    gtk_entry_set_max_length(GTK_ENTRY(ctx->phone_input), 6);

    gtk_entry_set_visibility(GTK_ENTRY(ctx->phone_input), TRUE);
}

static void switch_to_2fa_ui(LoginContext *ctx)
{
    ctx->stage = STAGE_2FA;

    if (ctx->phone_signal_id != 0) {
        g_signal_handler_disconnect(
            ctx->phone_input,
            ctx->phone_signal_id
        );

        ctx->phone_signal_id = 0;
    }

    gtk_label_set_text(
        GTK_LABEL(ctx->title),
        "Two-Step Verification"
    );

    gtk_label_set_text(
        GTK_LABEL(ctx->caption),
        "Enter your cloud password."
    );

    gtk_editable_set_text(GTK_EDITABLE(ctx->phone_input), "");

    gtk_entry_set_placeholder_text(
        GTK_ENTRY(ctx->phone_input),
        "Password"
    );

    gtk_entry_set_visibility(GTK_ENTRY(ctx->phone_input), FALSE);

    gtk_entry_set_max_length(GTK_ENTRY(ctx->phone_input), 128);
}

void telegram_handle_button_click(LoginContext *ctx)
{
    char json[512] = {0};

    const char *text =
        gtk_editable_get_text(GTK_EDITABLE(ctx->phone_input));

    switch (ctx->stage) {
    case STAGE_PHONE: {

        const char *country =
            gtk_editable_get_text(GTK_EDITABLE(ctx->reg_input));

        g_snprintf(
            json,
            sizeof(json),
            "{\"@type\":\"setAuthenticationPhoneNumber\","
            "\"phone_number\":\"%s%s\"}",
            country,
            text
        );

        break;
    }

    case STAGE_SMS:

        g_snprintf(
            json,
            sizeof(json),
            "{\"@type\":\"checkAuthenticationCode\","
            "\"code\":\"%s\"}",
            text
        );

        break;

    case STAGE_2FA:

        g_snprintf(
            json,
            sizeof(json),
            "{\"@type\":\"checkAuthenticationPassword\","
            "\"password\":\"%s\"}",
            text
        );

        break;

    default:
        return;
    }

    g_print("SEND: %s\n", json);

    td_json_client_send(ctx->td_client, json);
}

gboolean telegram_check_updates(gpointer data)
{
	
	char *api_id = load_env("API_ID");
    char *api_hash = load_env("API_HASH");
    LoginContext *ctx = data;

    const char *result =
        td_json_client_receive(ctx->td_client, 0.0);

    if (result == NULL)
        return TRUE;

    g_print("RECV: %s\n", result);

    if (g_strrstr(result, "\"@type\":\"error\"")) {
        g_warning("%s", result);
        return TRUE;
    }

    if (!g_strrstr(result, "updateAuthorizationState"))
        return TRUE;

    if (g_strrstr(result,
        "authorizationStateWaitTdlibParameters")) {
        char params[1024];
        printf("api_id=%p\n", (void *)api_id);
        printf("api_hash=%p\n", (void *)api_hash);
        
        printf("api_id=%s\n", api_id);
        printf("api_hash=%s\n", api_hash);
        snprintf(
            params,
            sizeof(params),
            "{"
            "\"@type\":\"setTdlibParameters\","
            "\"use_test_dc\":false,"
            "\"database_directory\":\"tdlib_db\","
            "\"files_directory\":\"tdlib_files\","
            "\"use_file_database\":true,"
            "\"use_chat_info_database\":true,"
            "\"use_message_database\":true,"
            "\"use_secret_chats\":true,"
            "\"system_language_code\":\"en\","
            "\"device_model\":\"Linux\","
            "\"system_version\":\"Arch Linux\","
            "\"application_version\":\"1.0\","
            "\"api_id\":%d,"
            "\"api_hash\":\"%s\""
            "}",
            atoi(api_id),
            api_hash
        );
        
        g_print("SEND:\n%s\n", params);
        
        td_json_client_send(ctx->td_client, params);
    }

    else if (g_strrstr(result,
        "authorizationStateWaitEncryptionKey")) {

        g_print("SEND: checkDatabaseEncryptionKey\n");

        td_json_client_send(
            ctx->td_client,
            "{\"@type\":\"checkDatabaseEncryptionKey\","
            "\"encryption_key\":\"\"}"
        );
    }

    else if (g_strrstr(result,
        "authorizationStateWaitPhoneNumber")) {

        g_print("STATE -> PHONE\n");

        switch_to_phone_ui(ctx);
    }

    else if (g_strrstr(result,
        "authorizationStateWaitCode")) {

        g_print("STATE -> SMS\n");

        switch_to_sms_ui(ctx);
    }

    else if (g_strrstr(result,
        "authorizationStateWaitPassword")) {

        g_print("STATE -> PASSWORD\n");

        switch_to_2fa_ui(ctx);
    }

    else if (g_strrstr(result,
        "authorizationStateReady")) {

        g_print("LOGIN SUCCESS\n");

        gtk_widget_set_visible(ctx->box, FALSE);
    }

    return TRUE;
}