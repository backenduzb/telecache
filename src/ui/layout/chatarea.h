#ifndef CHATAREA_H
#define CHATAREA_H

#include <gtk/gtk.h>

GtkWidget* create_chatarea_layout();
void chatarea_load_chat(long long chat_id);
void chatarea_append_message(const char* text, const char* time, int is_outgoing);

#endif