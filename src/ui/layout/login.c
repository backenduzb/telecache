#include "login.h"
#include "../../handlers/input.h"
#include "../../handlers/button.h"
#include "gtk/gtk.h"

GtkWidget *login_page_new(LoginContext *ctx) {
	ctx->stage = STAGE_LOADING;

    ctx->box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_widget_set_halign(ctx->box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(ctx->box, GTK_ALIGN_CENTER);
    gtk_widget_add_css_class(ctx->box, "login-page");

    ctx->title = gtk_label_new("Telecache authentication");
    gtk_widget_add_css_class(ctx->title, "login-title");
    gtk_label_set_xalign(GTK_LABEL(ctx->title), 0.0); 
    gtk_widget_set_size_request(ctx->title, 260, 30);
    gtk_box_append(GTK_BOX(ctx->box), ctx->title);

    ctx->caption = gtk_label_new("Please login to Telegram to save your data and deleted messages.");
    gtk_widget_add_css_class(ctx->caption, "login-caption");
    gtk_label_set_max_width_chars(GTK_LABEL(ctx->caption), 8);
    gtk_label_set_xalign(GTK_LABEL(ctx->caption), 0.0);
    gtk_label_set_wrap(GTK_LABEL(ctx->caption), TRUE);
    gtk_widget_set_size_request(ctx->caption, 260, 50);
    gtk_box_append(GTK_BOX(ctx->box), ctx->caption);

    ctx->inputs_con = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    
    ctx->reg_input = gtk_entry_new();
    gtk_widget_add_css_class(ctx->reg_input, "regen");
    gtk_entry_set_placeholder_text(GTK_ENTRY(ctx->reg_input), "+998");
    gtk_editable_set_width_chars(GTK_EDITABLE(ctx->reg_input), 5);
    gtk_editable_set_max_width_chars(GTK_EDITABLE(ctx->reg_input), 5);
    gtk_entry_set_max_length(GTK_ENTRY(ctx->reg_input), 5);
    gtk_editable_set_text(GTK_EDITABLE(ctx->reg_input), "+");
    gtk_editable_set_position(GTK_EDITABLE(ctx->reg_input), 1);
    g_signal_connect(G_OBJECT(ctx->reg_input), "changed", G_CALLBACK(on_reg_input_changed), NULL);

    ctx->phone_input = gtk_entry_new();
    gtk_widget_add_css_class(ctx->phone_input, "phone-input");
    gtk_entry_set_placeholder_text(GTK_ENTRY(ctx->phone_input), "-- --- -- --");
    gtk_editable_set_width_chars(GTK_EDITABLE(ctx->phone_input), 12);
    gtk_editable_set_max_width_chars(GTK_EDITABLE(ctx->phone_input), 12);
    gtk_entry_set_max_length(GTK_ENTRY(ctx->phone_input), 9); 
    
    ctx->phone_signal_id = g_signal_connect(G_OBJECT(ctx->phone_input), "changed", G_CALLBACK(on_phone_input_changed), NULL);

    gtk_box_append(GTK_BOX(ctx->inputs_con), ctx->reg_input);
    gtk_box_append(GTK_BOX(ctx->inputs_con), ctx->phone_input);
    gtk_box_append(GTK_BOX(ctx->box), ctx->inputs_con);

    ctx->button = gtk_button_new_with_label("Next");
    gtk_widget_add_css_class(ctx->button, "continue-button");
    
    GtkEventController *motion_ctrl = gtk_event_controller_motion_new();
    g_signal_connect(motion_ctrl, "enter", G_CALLBACK(on_button_enter), NULL);
    g_signal_connect(motion_ctrl, "leave", G_CALLBACK(on_button_leave), NULL);
    gtk_widget_add_controller(ctx->button, motion_ctrl);

    g_signal_connect(ctx->button, "clicked", G_CALLBACK(on_next_button_clicked), ctx);
    gtk_box_append(GTK_BOX(ctx->box), ctx->button);
    
    return ctx->box;
}