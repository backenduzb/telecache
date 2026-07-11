#ifndef TELEGRAM_INITALIZER_H
#define TELEGRAM_INITALIZER_H

#include "../../telegram/api/api.h"
#include "../../include/envloader.h"
#include "../../src/ui/layout/login.h"
#include <td/telegram/td_json_client.h>
#include "../handlers/login_handlers.h"


void initialize_tdlib(LoginContext *ctx);

#endif
