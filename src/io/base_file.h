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

#ifndef __BASE_FILE_H__
#define __BASE_FILE_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define BASE_TYPE_FILE base_file_get_type ()

G_DECLARE_DERIVABLE_TYPE (BaseFile, base_file, BASE, FILE, GObject)

struct _BaseFileClass
{
    GObjectClass parent_class;

    void (* parse_header) (BaseFile *f,
                           void     *buffer);

    void (* convert_data) (BaseFile *f,
                           void     *buffer,
                           guint64   num_samples);
};

BaseFile* base_file_new ();

G_END_DECLS

#endif
