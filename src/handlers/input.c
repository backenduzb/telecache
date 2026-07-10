#include "./input.h"

void on_phone_input_changed(GtkEditable *editable, gpointer data) {
    const char *text = gtk_editable_get_text(editable);
    char clean_text[32] = {0};
    int clean_idx = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        if (isdigit((unsigned char)text[i])) {
            clean_text[clean_idx++] = text[i];
        }
    }
    clean_text[clean_idx] = '\0';

    if (strcmp(text, clean_text) != 0) {
        g_signal_handlers_block_by_func(editable, G_CALLBACK(on_phone_input_changed), data);
        
        int pos = gtk_editable_get_position(editable);
        gtk_editable_set_text(editable, clean_text);
        gtk_editable_set_position(editable, pos);
        
        g_signal_handlers_unblock_by_func(editable, G_CALLBACK(on_phone_input_changed), data);
    }
}

void on_reg_input_changed(GtkEditable *editable, gpointer data) {
    const char *text = gtk_editable_get_text(editable);
    char clean_text[16] = {0};
    int clean_idx = 0;

    clean_text[clean_idx++] = '+';
    for (int i = 0; text[i] != '\0'; i++) {
        if (i == 0 && text[i] == '+') continue; 
        
        if (isdigit((unsigned char)text[i]) && clean_idx < 5) { 
            clean_text[clean_idx++] = text[i];
        }
    }
    clean_text[clean_idx] = '\0';

    if (strcmp(text, clean_text) != 0) {
        g_signal_handlers_block_by_func(editable, G_CALLBACK(on_reg_input_changed), data);
        
        int pos = gtk_editable_get_position(editable);
        gtk_editable_set_text(editable, clean_text);
        gtk_editable_set_position(editable, pos); 
        
        g_signal_handlers_unblock_by_func(editable, G_CALLBACK(on_reg_input_changed), data);
    }
}