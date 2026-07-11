#include "gio/gio.h"
#include "glib-object.h"
#include <gtk/gtk.h>
#include "../ui/windows/mainWindow.h"


static void activate(GtkApplication *app) {
	GtkWidget *window = main_window_new(app);
	gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
	GtkApplication *app;

	app = gtk_application_new("silf.tecacher.desktop", G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	int status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);
	return status;
}