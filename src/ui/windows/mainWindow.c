#include "./mainWindow.h"
#include "glib.h"
#include "gtk/gtkshortcut.h"
#include "../../../include/cssload.h"
#include "../layout/login.h"
#include <td/telegram/td_json_client.h>
#include "../../../telegram/api/api.h";
#include "../../../telegram/initalizer/initalize.h"


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
    td_json_client_execute(ctx->td_client, "{\"@type\": \"setLogVerbosityLevel\", \"new_verbosity_level\": 1}");
    
    GtkWidget *stack = gtk_stack_new();
    gtk_stack_set_transition_type(GTK_STACK(stack), GTK_STACK_TRANSITION_TYPE_CROSSFADE);
    gtk_box_append(GTK_BOX(root), stack);
    GtkWidget *loading_label = gtk_label_new("Yuklanmoqda...");
    gtk_stack_add_named(GTK_STACK(stack), loading_label, "loading");

    GtkWidget *login = login_page_new(ctx);
    gtk_widget_set_halign(login, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(login, GTK_ALIGN_CENTER);
    gtk_stack_add_named(GTK_STACK(stack), login, "login");

    GtkWidget *main_app_view = gtk_label_new("Asosiy Oyna (Siz tizimga kirgansiz!)"); 
    gtk_stack_add_named(GTK_STACK(stack), main_app_view, "main_app");

    ctx->stack = stack; 
    initialize_tdlib(ctx->td_client);

    g_timeout_add(100, telegram_check_updates, ctx);

    return window;
}