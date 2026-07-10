#ifndef TELEGRAM_HANDLERS_LOGIN_H
#define TELEGRAM_HANDLERS_LOGIN_H

#include "../../src/ui/layout/login.h"

gboolean telegram_check_updates(gpointer data);
void telegram_handle_button_click(LoginContext *ctx);

#endif