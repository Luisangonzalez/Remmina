/*
 * Remmina - The GTK+ Remote Desktop Client
 * Copyright (C) 2009-2011 Vic Lee
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * In addition, as a special exception, the copyright holders give
 * permission to link the code of portions of this program with the
 * OpenSSL library under certain conditions as described in each
 * individual source file, and distribute linked combinations
 * including the two.
 * You must obey the GNU General Public License in all respects
 * for all of the code used other than OpenSSL.
 * If you modify file(s) with this exception, you may extend this exception
 * to your version of the file(s), but you are not obligated to do so.
 * If you do not wish to do so, delete this exception statement from your
 * version.
 * If you delete this exception statement from all source
 * files in the program, then also delete it here.
 *
 */

#include <gtk/gtk.h>
#include <glib/gi18n.h>
#include "config.h"
#include "remmina_widget_pool.h"
#include "remmina_about.h"
#include "remmina/remmina_trace_calls.h"

void remmina_about_open(GtkWindow* parent)
{
    TRACE_CALL("remmina_about_open");

    const gchar* licenses[] =
    {
        N_("Remmina is free software; you can redistribute it and/or modify "
        "it under the terms of the GNU General Public License as published by "
        "the Free Software Foundation; either version 2 of the License, or "
        "(at your option) any later version."),
        N_("Remmina is distributed in the hope that it will be useful, "
        "but WITHOUT ANY WARRANTY; without even the implied warranty of "
        "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the "
        "GNU General Public License for more details."), N_(
        "You should have received a copy of the GNU General Public License "
        "along with this program; if not, write to the Free Software "
        "Foundation, Inc., 59 Temple Place, Suite 330, "
        "Boston, MA 02111-1307, USA.")
    };

    gchar* license = g_strjoin("\n\n", _(licenses[0]), _(licenses[1]), _(licenses[2]), NULL);

    GtkBuilder *builder;

    GtkWidget* aboutDialog;
    aboutDialog = gtk_about_dialog_new();

    builder=gtk_builder_new_from_file(REMMINA_UIDIR G_DIR_SEPARATOR_S "remmina_about.glade");
    aboutDialog=GTK_WIDGET(gtk_builder_get_object(builder, "remmina_about_open"));

    gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(aboutDialog), VERSION);
    if (parent)
    {
        gtk_window_set_transient_for(GTK_WINDOW(aboutDialog), parent);
        gtk_window_set_destroy_with_parent(GTK_WINDOW(aboutDialog), TRUE);
    }

    g_signal_connect(aboutDialog, "response", G_CALLBACK(gtk_widget_destroy), NULL);
    gtk_window_present(GTK_WINDOW(aboutDialog));

    remmina_widget_pool_register(aboutDialog);

    g_free(license);
}
