#ifndef LOGIN_H
#define LOGIN_H

#include <gtk/gtk.h>
#include "gtk/gtkshortcut.h"

typedef enum {
    STAGE_LOADING,
    STAGE_PHONE,
    STAGE_SMS,
    STAGE_2FA,
} AuthStage;

typedef struct {
	GtkWidget *box;
	GtkWidget *inputs_con;
	GtkWidget *reg_input;
	GtkWidget *phone_input;
	GtkWidget *button;
	GtkWidget *stack;
	GtkWidget *title;
	GtkWidget *caption;
	gpointer td_client;
	AuthStage stage;
	gulong phone_signal_id;

	gpointer api_ctx;
} LoginContext;

GtkWidget *login_page_new(LoginContext *ctx);

#endif