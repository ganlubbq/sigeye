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

#include "base_file.h"

typedef struct
{
    // Private members go here
}
BaseFilePrivate;

G_DEFINE_TYPE_WITH_PRIVATE (BaseFile, base_file, G_TYPE_OBJECT)

static void
base_file_finalize(GObject *obj)
{

    G_OBJECT_CLASS (base_file_parent_class)->finalize(obj);
}

static void
base_file_class_init(BaseFileClass *class)
{

}

static void
base_file_init(BaseFile *f)
{

}