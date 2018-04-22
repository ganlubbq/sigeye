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

#ifndef __SIGEYE_NOODLE_H__
#define __SIGEYE_NOODLE_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define SIGEYE_TYPE_NOODLE_WINDOW (sigeye_noodle_window_get_type ())

G_DECLARE_FINAL_TYPE (SigeyeNoodleWindow, sigeye_noodle_window, SIGEYE, NOODLE_WINDOW, GtkApplicationWindow)

SigeyeNoodleWindow* sigeye_noodle_window_new    (GtkApplication *app);
void                sigeye_noodle_window_open   (SigeyeNoodleWindow *win,
                                                 GFile              *file);

G_END_DECLS

#endif
