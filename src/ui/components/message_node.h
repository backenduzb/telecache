#ifndef MESSAGE_NODE_H
#define MESSAGE_NODE_H

#include <gtk/gtk.h>

typedef struct {
    long long message_id;
    char text[1024];
    char time[16];
    int is_outgoing; 
} MessageModel;

GtkWidget* create_message_node_widget(MessageModel model);

#endif 