#include "message_node.h"

GtkWidget* create_message_node_widget(MessageModel model) {
    GtkWidget *row_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget *bubble = gtk_box_new(GTK_ORIENTATION_VERTICAL, 4);
    
    GtkWidget *lbl_text = gtk_label_new(model.text);
    gtk_label_set_wrap(GTK_LABEL(lbl_text), TRUE);
    gtk_label_set_max_width_chars(GTK_LABEL(lbl_text), 50);
    gtk_label_set_xalign(GTK_LABEL(lbl_text), 0.0);

    GtkWidget *lbl_time = gtk_label_new(model.time);
    gtk_widget_add_css_class(lbl_time, "message-time");
    gtk_label_set_xalign(GTK_LABEL(lbl_time), 1.0);

    gtk_box_append(GTK_BOX(bubble), lbl_text);
    gtk_box_append(GTK_BOX(bubble), lbl_time);

    if (model.is_outgoing) {
        gtk_widget_add_css_class(bubble, "message-outgoing");
        GtkWidget *spacer = gtk_label_new(""); 
        gtk_widget_set_hexpand(spacer, TRUE);
        gtk_box_append(GTK_BOX(row_box), spacer);
        gtk_box_append(GTK_BOX(row_box), bubble);
    } else {
        gtk_widget_add_css_class(bubble, "message-incoming");
        gtk_box_append(GTK_BOX(row_box), bubble);
        GtkWidget *spacer = gtk_label_new("");
        gtk_widget_set_hexpand(spacer, TRUE);
        gtk_box_append(GTK_BOX(row_box), spacer);
    }

    return row_box;
}