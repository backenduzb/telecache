#include "./button.h"
#include "../ui/layout/login.h"
#include "../../telegram/handlers/login_handlers.h"

void on_button_enter(GtkEventControllerMotion *controller, double x, double y, gpointer user_data) {
	GtkWidget *widget = gtk_event_controller_get_widget(GTK_EVENT_CONTROLLER(controller));
	GdkCursor *cursor = gdk_cursor_new_from_name("pointer", NULL);
	gtk_widget_set_cursor(widget, cursor);
	g_object_unref(cursor);
}

void on_button_leave(GtkEventControllerMotion *controller, gpointer user_data) {
	GtkWidget *widget = gtk_event_controller_get_widget(GTK_EVENT_CONTROLLER(controller));
	gtk_widget_set_cursor(widget, NULL);
}

void on_next_button_clicked(GtkButton *button, gpointer user_data) {
	LoginContext *ctx = (LoginContext *)user_data;
	if (ctx->stage == STAGE_LOADING) {
	    return;
	}
	telegram_handle_login_button_click(ctx);
}