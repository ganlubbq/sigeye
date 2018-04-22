/*
 * This file is part of SigEye.
 *
 * SigEye is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SigEye is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with SigEye.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <gtk/gtk.h>

#include "sigeye.h"

static gchar *db_file = NULL;

static const GOptionEntry cli_entries[] =
{
    { "database", 'd', G_OPTION_FLAG_NONE, G_OPTION_ARG_FILENAME, &db_file, "SQLite3 database FILE", "FILE" },
    { NULL }
};

static void
app_activate(GtkApplication *app)
{
    // TODO
}

void
sigeye_open(GtkApplication *app, gpointer files, gint n_files, gchar *hint)
{
    // TODO
}

int
main(int argc, char *argv[])
{
    GtkApplication *app = gtk_application_new("com.github.daulpavid.sigeye",
                                              G_APPLICATION_HANDLES_OPEN);

    g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);
    g_signal_connect(app, "open", G_CALLBACK(sigeye_open), NULL);

    g_application_add_main_option_entries(G_APPLICATION(app), cli_entries);

    int status = g_application_run(G_APPLICATION(app), argc, argv);

    g_object_unref(app);

    return status;
}
