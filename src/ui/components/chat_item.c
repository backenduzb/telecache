#include "chat_item.h"

typedef struct {
    long long chat_id;
    void (*callback)(long long);
} ChatClickData;

static void on_item_clicked(GtkButton* button, gpointer user_data) {
    ChatClickData* data = (ChatClickData*)user_data;
    if (data && data->callback) {
        data->callback(data->chat_id);
    }
}

static void free_click_data(gpointer data, GClosure* closure) {
    g_free(data);
}

GtkWidget* create_chat_item_widget(ChatItemModel model, void (*on_chat_click)(long long chat_id)) {
    GtkWidget *button = gtk_button_new();
    gtk_widget_add_css_class(button, "chat-item-button");

    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    GtkWidget *text_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
    GtkWidget *meta_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    GtkWidget *lbl_title = gtk_label_new(model.title);
    gtk_widget_add_css_class(lbl_title, "chat-item-title");
    gtk_label_set_xalign(GTK_LABEL(lbl_title), 0.0);

    GtkWidget *lbl_msg = gtk_label_new(model.last_message);
    gtk_widget_add_css_class(lbl_msg, "chat-item-msg");
    gtk_label_set_xalign(GTK_LABEL(lbl_msg), 0.0);
    gtk_label_set_ellipsize(GTK_LABEL(lbl_msg), PANGO_ELLIPSIZE_END);

    gtk_box_append(GTK_BOX(text_box), lbl_title);
    gtk_box_append(GTK_BOX(text_box), lbl_msg);
    gtk_widget_set_hexpand(text_box, TRUE);

    GtkWidget *lbl_time = gtk_label_new(model.time);
    gtk_widget_add_css_class(lbl_time, "chat-item-time");
    gtk_box_append(GTK_BOX(meta_box), lbl_time);

    if (model.unread_count > 0) {
        char count_str[16];
        snprintf(count_str, sizeof(count_str), "%d", model.unread_count);
        GtkWidget *lbl_count = gtk_label_new(count_str);
        gtk_widget_add_css_class(lbl_count, "chat-item-counter");
        gtk_box_append(GTK_BOX(meta_box), lbl_count);
    }

    gtk_box_append(GTK_BOX(main_box), text_box);
    gtk_box_append(GTK_BOX(main_box), meta_box);
    gtk_button_set_child(GTK_BUTTON(button), main_box);

    ChatClickData *click_data = g_new0(ChatClickData, 1);
    click_data->chat_id = model.chat_id;
    click_data->callback = on_chat_click;

    g_signal_connect_data(button, "clicked", G_CALLBACK(on_item_clicked), click_data, free_click_data, 0);

    return button;
}