#ifndef CHATLIST_H
#define CHATLIST_H

#include <gtk/gtk.h>

GtkWidget* create_chatlist_layout();
void on_chat_selected(long long chat_id);

#endif 