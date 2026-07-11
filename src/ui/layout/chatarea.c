#include "chatarea.h"
#include "../components/message_node.h"

static GtkWidget *title_label = NULL;
static GtkWidget *subtitle_label = NULL;
static GtkWidget *messages_box = NULL;
static GtkWidget *message_entry = NULL;
static long long current_chat_id = 0;

static void on_send_clicked(GtkButton* button, gpointer user_data) {
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(message_entry));
    const char *text = gtk_entry_buffer_get_text(buffer);
    
    if (strlen(text) > 0 && current_chat_id != 0) {
        chatarea_append_message(text, "10:54", 1);
        gtk_entry_buffer_set_text(buffer, "", 0); 
    }
}


GtkWidget* create_chatarea_layout() {
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_add_css_class(main_box, "chat-area-container");
    gtk_widget_set_hexpand(main_box, TRUE);

    GtkWidget *title_panel = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
    gtk_widget_add_css_class(title_panel, "chat-title-panel");
    
    title_label = gtk_label_new("Chat tanlanmagan");
    gtk_widget_add_css_class(title_label, "chat-header-title");
    gtk_label_set_xalign(GTK_LABEL(title_label), 0.0);
    
    subtitle_label = gtk_label_new("");
    gtk_widget_add_css_class(subtitle_label, "chat-header-subtitle");
    gtk_label_set_xalign(GTK_LABEL(subtitle_label), 0.0);

    gtk_box_append(GTK_BOX(title_panel), title_label);
    gtk_box_append(GTK_BOX(title_panel), subtitle_label);
    gtk_box_append(GTK_BOX(main_box), title_panel);

    GtkWidget *scroll = gtk_scrolled_window_new();
    gtk_widget_set_vexpand(scroll, TRUE);
    
    messages_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_add_css_class(messages_box, "chat-messages-box");
    
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scroll), messages_box);
    gtk_box_append(GTK_BOX(main_box), scroll);

    GtkWidget *input_panel = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_add_css_class(input_panel, "chat-input-panel");

    message_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(message_entry), "Write a message...");
    gtk_widget_set_hexpand(message_entry, TRUE);
    g_signal_connect(message_entry, "activate", G_CALLBACK(on_send_clicked), NULL);

    GtkWidget *send_button = gtk_button_new_with_label("Yuborish");
    gtk_widget_add_css_class(send_button, "chat-send-button");
    g_signal_connect(send_button, "clicked", G_CALLBACK(on_send_clicked), NULL);

    gtk_box_append(GTK_BOX(input_panel), message_entry);
    gtk_box_append(GTK_BOX(input_panel), send_button);
    gtk_box_append(GTK_BOX(main_box), input_panel);

    return main_box;
}

void chatarea_load_chat(long long chat_id) {
    current_chat_id = chat_id;
    
    GtkWidget *child;
    while ((child = gtk_widget_get_first_child(messages_box)) != NULL) {
        gtk_box_remove(GTK_BOX(messages_box), child);
    }

    if (chat_id == 1) {
        gtk_label_set_text(GTK_LABEL(title_label), "User");
        gtk_label_set_text(GTK_LABEL(subtitle_label), "online");

        chatarea_append_message("Assalomu alaykum!", "11:00", 0);
        chatarea_append_message("askvkdfkjbadfkjbkdbkjfaakjbkjfad", "11:02", 1);
        chatarea_append_message("dsjvnasjkdankvadkjfbdkjbkjdakfkjadbkjad", "11:05", 0);
        chatarea_append_message("bu o'o'o'ta uzun habar buni container eplay oladimikin eplay olmasa max_width_char bilan max width meramiz hihihi.", "11:05", 0);
    } 
     
    else {
        gtk_label_set_text(GTK_LABEL(title_label), "Telegram Bot API");
        gtk_label_set_text(GTK_LABEL(subtitle_label), "bot");

        chatarea_append_message("Webhook successfully updated.", "05 Jul", 0);
    }
}

void chatarea_append_message(const char* text, const char* time, int is_outgoing) {
    MessageModel model;
    model.message_id = 0;
    g_strlcpy(model.text, text, sizeof(model.text));
    g_strlcpy(model.time, time, sizeof(model.time));
    model.is_outgoing = is_outgoing;

    GtkWidget *msg_widget = create_message_node_widget(model);
    gtk_box_append(GTK_BOX(messages_box), msg_widget);
    
    GtkAdjustment *adj = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(gtk_widget_get_parent(messages_box)));
    if (adj) {
        gtk_adjustment_set_value(adj, gtk_adjustment_get_upper(adj));
    }
}