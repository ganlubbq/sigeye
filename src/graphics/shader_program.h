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

#ifndef __SHADER_PROGRAM_H__
#define __SHADER_PROGRAM_H__

#include "shader.h"

#include <glib-object.h>

G_BEGIN_DECLS

#define SHADER_TYPE_PROGRAM (shader_program_get_type ())

G_DECLARE_FINAL_TYPE (ShaderProgram, shader_program, SHADER, PROGRAM, GObject)

ShaderProgram* shader_program_new       ();
ShaderProgram* shader_program_new_from  (gint arg_count, ...);

void           shader_program_attach    (ShaderProgram *s,
                                         Shader  *shader);
void           shader_program_detach    (ShaderProgram *s,
                                         Shader  *shader);
void           shader_program_bind_frag (ShaderProgram *s,
                                         GLuint         color_num,
                                         const gchar   *name);

GLuint         shader_program_frag      (ShaderProgram *s,
                                         const gchar *name);

void           shader_program_link      (ShaderProgram *s);

void           shader_program_delete    (ShaderProgram *s);

G_END_DECLS

#endif
