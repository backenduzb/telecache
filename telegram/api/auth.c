#include "./api.h"

gboolean telegram_check_updates(gpointer data)
{
	LoginContext *ctx = data;
    if (ctx == NULL) return TRUE;

    const char *result = td_json_client_receive(ctx->td_client, 0.0);
    if (result == NULL) return TRUE;

    g_print("RECV: %s\n", result);

    if (g_strrstr(result, "\"@type\":\"error\"")) {
        g_warning("TDLib error: %s", result);
        return TRUE;
    }

    if (!g_strrstr(result, "updateAuthorizationState"))
        return TRUE;

    if (g_strrstr(result, "authorizationStateWaitTdlibParameters")) {
        if (ctx->api_ctx == NULL) {
            return TRUE;
        }

        ApiContext *api_context = (ApiContext *)ctx->api_ctx;

        if (api_context->api_id == NULL || api_context->api_hash == NULL) {
            return TRUE;
        }

        char params[1024];
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
            atoi(api_context->api_id),
            api_context->api_hash
        );

        td_json_client_send(ctx->td_client, params);
    }

    if (g_strrstr(result, "authorizationStateWaitEncryptionKey")) {
        td_json_client_send(
            ctx->td_client,
            "{\"@type\":\"checkDatabaseEncryptionKey\",\"encryption_key\":\"\"}"
        );
    }

    else if (g_strrstr(result, "authorizationStateWaitPhoneNumber")) {
        switch_to_phone_ui(ctx);
    }

    else if (g_strrstr(result, "authorizationStateWaitCode")) {
        switch_to_sms_ui(ctx);
    }

    else if (g_strrstr(result, "authorizationStateWaitPassword")) {
        switch_to_2fa_ui(ctx);
    }

    else if (g_strrstr(result, "authorizationStateReady")) {
        gtk_widget_set_visible(ctx->box, FALSE);
    }

    return TRUE;
}
