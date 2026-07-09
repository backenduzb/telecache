#include "./mainWindow.h"
#include "gtk/gtkshortcut.h"
#include "../../../include/cssload.h"
#include "../layout/login.h"

GtkWidget *main_window_new(GtkApplication *app) {
    GtkWidget *window;

    window = gtk_application_window_new(app);

    gtk_window_set_title(GTK_WINDOW(window),
                         "Telegram");

    gtk_window_set_default_size(GTK_WINDOW(window),
                                1200,
                                800);

    GtkWidget *login = login_page_new();

    gtk_window_set_child(GTK_WINDOW(window),
                         login);
    load_css("assets/styles/main.css");
    return window;
}