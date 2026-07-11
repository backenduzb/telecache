#ifndef TELEGRAM_API_H
#define TELEGRAM_API_H

#include <glib.h>
#include "../../src/ui/layout/login.h"
#include <td/telegram/td_json_client.h>
#include "../handlers/login_handlers.h"


typedef struct {
	char *api_id;
	char *api_hash;
} ApiContext;

gboolean telegram_check_updates(gpointer data);

#endif