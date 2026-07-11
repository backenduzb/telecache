#ifndef TELEGRAM_HANDLERS_LOGIN_H
#define TELEGRAM_HANDLERS_LOGIN_H

#include "../../src/ui/layout/login.h"

void switch_to_phone_ui(LoginContext *ctx);
void switch_to_sms_ui(LoginContext *ctx);
void switch_to_2fa_ui(LoginContext *ctx);
void telegram_handle_login_button_click(LoginContext *ctx);

#endif
