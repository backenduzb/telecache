#include "./login.h"

GtkWidget *login_page_new(void) {
	GtkWidget *box;
	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
	gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
	gtk_widget_set_valign(box, GTK_ALIGN_CENTER);

	GtkWidget *title;
	title = gtk_label_new("Telecache");
	gtk_widget_add_css_class(title, "login-title");
	gtk_box_append(GTK_BOX(box), title);

	GtkWidget *phone_input;
	phone_input = gtk_entry_new();
	gtk_widget_add_css_class(phone_input, "phone-input");
	gtk_entry_set_placeholder_text(GTK_ENTRY(phone_input), "+998 93 350 19 77");
	gtk_box_append(GTK_BOX(box), phone_input);
	
	GtkWidget *button;
	button = gtk_button_new_with_label("Sign in");
	gtk_widget_add_css_class(button, "continue-button");
	gtk_box_append(GTK_BOX(box), button);
	
	return box;
}