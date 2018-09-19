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

#ifndef __SHADER_H__
#define __SHADER_H__

#include <glib-object.h>

#include <GL/gl3w.h>

G_BEGIN_DECLS

#define SHADER_TYPE (shader_get_type ())

G_DECLARE_FINAL_TYPE (Shader, shader, SHADER, OBJECT, GObject)

Shader*  shader_new                 (const gchar *path, GLenum shader_type);
void     shader_compile_source      (Shader      *s,
                                     GLenum       shader_type,
                                     const gchar *shader_contents,
                                     gsize        shader_size);

gboolean shader_find_file           (Shader *s, const gchar *path);

void     shader_load_file           (Shader  *s,
                                     gchar  **shader_contents,
                                     gsize   *shader_size);

gboolean shader_compiled            (Shader *s);
gchar*   shader_file_name           (Shader *s);
GLuint   shader_id                  (Shader *s);
void     shader_delete              (Shader *s);

G_END_DECLS

#endif
