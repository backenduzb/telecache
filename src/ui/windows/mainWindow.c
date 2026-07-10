#include "./mainWindow.h"
#include "glib.h"
#include "gtk/gtkshortcut.h"
#include "../../../include/cssload.h"
#include "../layout/login.h"
#include <td/telegram/td_json_client.h>
#include "../../../telegram/handlers/login.h"

GtkWidget *main_window_new(GtkApplication *app) {
	GtkWidget *window = gtk_application_window_new(app);

	gtk_window_set_title(GTK_WINDOW(window), "Telegram");
	gtk_window_set_default_size(GTK_WINDOW(window), 1200, 800);
	
	load_css("assets/styles/main.css");

	GtkWidget *root = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	
	gtk_widget_add_css_class(root, "root");
	
	gtk_widget_set_hexpand(root, TRUE);
	gtk_widget_set_vexpand(root, TRUE);
	
	gtk_window_set_child(GTK_WINDOW(window), root);

	LoginContext *ctx = g_new0(LoginContext, 1);
	ctx->td_client = td_json_client_create();
	GtkWidget *login = login_page_new(ctx);

	gtk_widget_set_halign(login, GTK_ALIGN_CENTER);
	gtk_widget_set_valign(login, GTK_ALIGN_CENTER);
	
	gtk_widget_set_hexpand(login, TRUE);
	gtk_widget_set_vexpand(login, TRUE);
	
	gtk_box_append(GTK_BOX(root), login);

	g_timeout_add(100, telegram_check_updates, ctx);

	return window;
}