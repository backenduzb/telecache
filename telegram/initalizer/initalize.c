#include "./initalize.h"

void initialize_tdlib(LoginContext *ctx) {
    if (ctx == NULL) {
        return;
    }
    if (ctx->td_client == NULL) {
        g_printerr("\n[KATTA XATO] ctx->td_client o'zi NULL bo'lib yotibdi! Shuning uchun segfault beryapti!\n");
        g_printerr("Iltimos, td_json_client_create() funksiyasi chaqirilganini tekshiring.\n\n");
        return;
    }

    char *api_id_str = load_env("API_ID");
    char *api_hash_str = load_env("API_HASH");

    if (api_id_str == NULL || api_hash_str == NULL) {
        return;
    }

    ApiContext *apictx = g_new0(ApiContext, 1);

    apictx->api_id = g_strdup(api_id_str);
    apictx->api_hash = g_strdup(api_hash_str);
    ctx->api_ctx = apictx;

    int api_id = atoi(apictx->api_id);
    char *parameters_json = g_strdup_printf(
        "{"
        "\"@type\": \"setTdlibParameters\","
        "\"use_test_dc\": false,"
        "\"database_directory\": \"tdlib_db\","
        "\"files_directory\": \"tdlib_files\","
        "\"use_file_database\": true,"
        "\"use_chat_info_database\": true,"
        "\"use_message_database\": true,"
        "\"use_secret_chats\": false,"
        "\"api_id\": %d,"
        "\"api_hash\": \"%s\","
        "\"system_language_code\": \"en\","
        "\"device_model\": \"Desktop\","
        "\"system_version\": \"Linux\","
        "\"application_version\": \"1.0.0\","
        "\"enable_storage_optimizer\": true"
        "}", api_id, apictx->api_hash
    );
    td_json_client_send(ctx->td_client, parameters_json);
    g_free(parameters_json);
}
