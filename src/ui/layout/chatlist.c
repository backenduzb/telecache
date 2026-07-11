#include "chatlist.h"
#include "../components/chat_item.h"
#include "chatarea.h"

void on_chat_selected(long long chat_id) {
    chatarea_load_chat(chat_id);
}

GtkWidget* create_chatlist_layout() {
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_add_css_class(main_box, "chat-list-container");

    GtkWidget *search_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(search_entry), "Search");
    gtk_widget_add_css_class(search_entry, "chat-search-bar");
    gtk_box_append(GTK_BOX(main_box), search_entry);

    GtkWidget *scroll = gtk_scrolled_window_new();
    gtk_widget_set_vexpand(scroll, TRUE);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);

    GtkWidget *list_box = gtk_list_box_new();
    gtk_list_box_set_selection_mode(GTK_LIST_BOX(list_box), GTK_SELECTION_SINGLE);
    gtk_list_box_set_show_separators(GTK_LIST_BOX(list_box), FALSE);
    
    ChatItemModel mock_chats[] = {
        {1, "Chat title", "Yangi habarni habarini habari habardan habar", "10:42", 15}
    };
    
    for (int i = 0; i < 5; i++) {
        GtkWidget *item_widget = create_chat_item_widget(mock_chats[0], on_chat_selected);
        gtk_list_box_append(GTK_LIST_BOX(list_box), item_widget);
    }
    
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scroll), list_box);
    gtk_box_append(GTK_BOX(main_box), scroll);

    return main_box;
}