#include "./login_handlers.h"
#include <gtk/gtk.h>
#include <glib.h>
#include <td/telegram/td_json_client.h>
#include "../api/api.h"

void switch_to_phone_ui(LoginContext *ctx)
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

void switch_to_sms_ui(LoginContext *ctx)
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

void switch_to_2fa_ui(LoginContext *ctx)
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

void telegram_handle_login_button_click(LoginContext *ctx)
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

