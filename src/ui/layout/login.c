#include "./login.h"
#include "gdk/gdk.h"
#include "gtk/gtk.h"
#include "gtk/gtkshortcut.h"

GtkWidget *login_page_new(void) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
    
    gtk_widget_add_css_class(box, "login-page");

    GtkWidget *title = gtk_label_new("Telecache login");
    gtk_widget_add_css_class(title, "login-title");
    gtk_box_append(GTK_BOX(box), title);

    GtkWidget *inputs_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    
    GtkWidget *reg_phone_input = gtk_entry_new();
    gtk_widget_add_css_class(reg_phone_input, "reg-phone-input");
    gtk_entry_set_placeholder_text(GTK_ENTRY(reg_phone_input), "+998");
    
    GtkWidget *phone_input = gtk_entry_new();
    gtk_widget_add_css_class(phone_input, "phone-input");
    gtk_entry_set_placeholder_text(GTK_ENTRY(phone_input), "93 350 15 98");

    gtk_box_append(GTK_BOX(inputs_box), reg_phone_input);
    gtk_box_append(GTK_BOX(inputs_box), phone_input);
    
    gtk_box_append(GTK_BOX(box), inputs_box);
    
    GtkWidget *button = gtk_button_new_with_label("Next");
    gtk_widget_add_css_class(button, "continue-button");
    gtk_box_append(GTK_BOX(box), button);
    
    return box;
}