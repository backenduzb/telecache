#include "./mainWindow.h"
#include "glib.h"
#include "gtk/gtk.h"
#include "gtk/gtkshortcut.h"
#include "../../../include/cssload.h"
#include "../layout/login.h"
#include <td/telegram/td_json_client.h>
#include "../../../telegram/api/api.h"
#include "../../../telegram/initalizer/initalize.h"

#include "../layout/chatlist.h"
#include "../layout/chatarea.h"

GtkWidget *main_window_new(GtkApplication *app) {
    GtkWidget *window = gtk_application_window_new(app);

    gtk_window_set_title(GTK_WINDOW(window), "Telegram Desktop");
    gtk_window_set_default_size(GTK_WINDOW(window), 1200, 800);
    
    load_css("assets/styles/main.css");

    GtkWidget *root = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_add_css_class(root, "root");
    gtk_window_set_child(GTK_WINDOW(window), root);

    GtkWidget *stack = gtk_stack_new();
    gtk_stack_set_transition_type(GTK_STACK(stack), GTK_STACK_TRANSITION_TYPE_CROSSFADE);
    gtk_widget_add_css_class(GTK_WIDGET(stack), "stack-widget");
    gtk_widget_set_hexpand(stack, TRUE);
    gtk_widget_set_vexpand(stack, TRUE);
    gtk_box_append(GTK_BOX(root), stack);

    GtkWidget *main_app_view = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_widget_add_css_class(main_app_view, "paned-widget");
    gtk_widget_set_hexpand(main_app_view, TRUE);
    gtk_widget_set_vexpand(main_app_view, TRUE);

    GtkWidget *chatlist_panel = create_chatlist_layout();
    GtkWidget *chatarea_panel = create_chatarea_layout();

    gtk_paned_set_start_child(GTK_PANED(main_app_view), chatlist_panel);
    gtk_paned_set_end_child(GTK_PANED(main_app_view), chatarea_panel);
    gtk_paned_set_position(GTK_PANED(main_app_view), 640); 

    gtk_stack_add_named(GTK_STACK(stack), main_app_view, "main_app");

    gtk_stack_set_visible_child_name(GTK_STACK(stack), "main_app");

    LoginContext *ctx = g_new0(LoginContext, 1);
    ctx->td_client = td_json_client_create();
    ctx->stack = stack;

    chatarea_load_chat(1001);

    return window;
}