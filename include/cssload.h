#ifndef CSSLOAD_H
#define CSSLOAD_H

#include "gdk/gdk.h"
#include "glib-object.h"
#include "gtk/gtkcssprovider.h"
#include <gtk/gtk.h>

#include <glib.h>

void load_css(const char *path)
{
    g_print("Loading CSS: %s\n", path);

    if (!g_file_test(path, G_FILE_TEST_EXISTS)) {
        g_print("❌ CSS file not found!\n");
        return;
    }

    GtkCssProvider *provider = gtk_css_provider_new();

    gtk_css_provider_load_from_path(provider, path);

    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    g_object_unref(provider);

    g_print("✅ CSS loaded\n");
}

#endif