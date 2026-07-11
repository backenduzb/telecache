#ifndef CHAT_ITEM_H
#define CHAT_ITEM_H

#include <gtk/gtk.h>

typedef struct {
    long long chat_id;
    char title[128];
    char last_message[256];
    char time[16];
    int unread_count;
} ChatItemModel;

GtkWidget* create_chat_item_widget(ChatItemModel model, void (*on_chat_click)(long long chat_id));

#endif 