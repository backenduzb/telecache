#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <gtk/gtk.h>
#include <ctype.h>

void on_reg_input_changed(GtkEditable *editable, gpointer data);
void on_phone_input_changed(GtkEditable *editable, gpointer data);

#endif