#ifndef BUTTON_HANDLER_H
#define BUTTON_HANDLER_H

#include <gtk/gtk.h>

void on_button_enter(GtkEventControllerMotion *controller, double x, double y, gpointer user_data);
void on_button_leave(GtkEventControllerMotion *controller, gpointer user_data);
void on_next_button_clicked(GtkButton *button, gpointer user_data);

#endif