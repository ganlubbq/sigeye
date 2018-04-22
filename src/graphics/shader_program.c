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

#include "shader_program.h"
#include "shader.h"

#include <stdio.h>

struct _ShaderProgram
{
    GSList* shader_list;

    GLuint program_id;

    gboolean program_linked;
};

G_DEFINE_TYPE (ShaderProgram, shader_program, G_TYPE_OBJECT)

static void
shader_program_link_emit(ShaderProgram *s, gboolean program_linked)
{
    s->program_linked = program_linked;
    g_signal_emit_by_name(s, "shader-program-linked", s->program_linked);
}

static void
shader_compiled_cb(Shader   *s,
                   gboolean  shader_compiled,
                   gpointer  user_data)
{
    if (shader_compiled)
    {
        shader_program_link(SHADER_PROGRAM(user_data));
    }
    else
    {
        fprintf(stderr, "[FAIL] - Shader program failed to re-link: %s\n",
                shader_file_name(s));
    }
}

ShaderProgram*
shader_program_new()
{
    return g_object_new(SHADER_TYPE_PROGRAM, NULL);
}

ShaderProgram*
shader_program_new_from(gint arg_count, ...)
{
    ShaderProgram *s = g_object_new(SHADER_TYPE_PROGRAM, NULL);

    va_list args;
    va_start(args, arg_count);
    for (gint i = 0; i < arg_count; i++)
    {
        Shader *shader = va_arg(args, Shader*);
        s->shader_list = g_slist_prepend(s->shader_list, shader);
    }
    va_end(args);

    return s;
}

void
shader_program_attach(ShaderProgram *s, Shader *shader)
{
    g_signal_connect(shader, "shader-compiled", G_CALLBACK(shader_compiled_cb), s);

    glAttachShader(s->program_id, shader_id(shader));

    s->shader_list = g_slist_prepend(s->shader_list, shader);
}

void
shader_program_detach(ShaderProgram *s, Shader *shader)
{
    glDetachShader(s->program_id, shader_id(shader));

    s->shader_list = g_slist_remove(s->shader_list, shader);
}

void
shader_program_bind_frag(ShaderProgram *s,
                         GLuint         color_num,
                         const gchar   *name)
{
    glBindFragDataLocation(s->program_id, color_num, name);
}

GLuint
shader_program_get_frag(ShaderProgram *s, 
                        const gchar *name)
{
    return glGetFragDataLocation(s->program_id, name);
}

void
shader_program_link(ShaderProgram *s)
{
    glLinkProgram(s->program_id);

    GLchar program_log[GL_LOG_SIZE];
    glGetProgramInfoLog(s->program_id, GL_LOG_SIZE, NULL, program_log);
    printf("[INFO] - OpenGL program log: %s\n", program_log);

    GLint status;
    glGetProgramiv(s->program_id, GL_LINK_STATUS, &status);
    if (status == GL_TRUE)
    {
        shader_program_link_emit(s, TRUE);
    }
    else
    {
        fprintf(stderr, "[FAIL] - Unable to link shader program\n");
        shader_program_link_emit(s, FALSE);
    }
}

static void
shader_program_destroy_cb(gpointer data)
{
    g_object_unref((Shader *) data);
}

void
shader_program_delete(ShaderProgram *s)
{
    g_slist_free_full(s->shader_list, shader_program_destroy_cb);
    glDeleteProgram(s->program_id);
}

static void
shader_program_finalize(GObject *obj)
{
    shader_program_delete(SHADER_PROGRAM(obj));

    G_OBJECT_CLASS (shader_program_parent_class)->finalize(obj);
}

static void
shader_program_class_init(ShaderProgramClass *class)
{
    g_signal_new("shader-program-linked",
                 G_TYPE_FROM_CLASS(class),
                 G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE,
                 0, NULL, NULL, NULL,
                 G_TYPE_NONE, 1, G_TYPE_BOOLEAN);
}

static void
shader_program_init(ShaderProgram *s)
{
    s->shader_list = g_slist_alloc();
    s->program_id = glCreateProgram();
}