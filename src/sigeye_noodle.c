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

#include "sigeye_noodle.h"

struct _SigeyeNoodleWindow
{
    GtkApplicationWindow parent_instance;
};

G_DEFINE_TYPE(SigeyeNoodleWindow, sigeye_noodle_window, GTK_TYPE_APPLICATION_WINDOW)

SigeyeNoodleWindow*
sigeye_noodle_window_new(GtkApplication *app)
{
    SigeyeNoodleWindow *window;
    window = g_object_new(SIGEYE_TYPE_NOODLE_WINDOW, "application", app, NULL);
    return window;
}

void
sigeye_noodle_window_open(SigeyeNoodleWindow *win, GFile *file)
{

}

static void
sigeye_noodle_window_class_init(SigeyeNoodleWindowClass *class)
{
}

static void
sigeye_noodle_window_init(SigeyeNoodleWindow *win)
{

}
