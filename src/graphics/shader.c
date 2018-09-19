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

#include "shader.h"

#include <gio/gio.h>

#include <stdio.h>

#define GL_LOG_SIZE 1024

struct _Shader
{
    GFile* file;

    GFileMonitor* file_monitor;

    gchar* file_name;

    GLenum shader_type;
    GLuint shader_id;

    gboolean shader_compiled;
};

G_DEFINE_TYPE (Shader, shader, G_TYPE_OBJECT)

static void
shader_compiled_emit(Shader *s, gboolean shader_compiled)
{
    s->shader_compiled = shader_compiled;
    g_signal_emit_by_name(s, "shader-compiled", s->shader_compiled);
}

static void
shader_changed_emit(Shader *s)
{
    g_signal_emit_by_name(s, "shader-changed", NULL);
}

static void
shader_changed_cb(GFileMonitor     *monitor,
                  GFile            *file,
                  GFile            *other_file,
                  GFileMonitorEvent event_type,
                  gpointer          user_data)
{
    Shader *s = SHADER_OBJECT(user_data);

    shader_changed_emit(s);

    g_autofree gchar *shader_contents = NULL;
    gsize shader_size = 0;

    shader_load_file(s, &shader_contents, &shader_size);
    shader_compile_source(s, s->shader_type, shader_contents, shader_size);
}

static void
shader_monitor_file(Shader *s)
{
    s->file_monitor = g_file_monitor_file(s->file, G_FILE_MONITOR_NONE, NULL, NULL);
    if (s->file_monitor == NULL)
    {
        fprintf(stderr, "[FAIL] - Unable to monitor shader file: %s\n", s->file_name);
        return;
    }

    g_signal_connect(s->file_monitor, "changed", G_CALLBACK(shader_changed_cb), s);
}

Shader*
shader_new(const gchar *path, GLenum shader_type)
{
    Shader *s = g_object_new(SHADER_TYPE, NULL);
    if (shader_find_file(s, path))
    {
        g_autofree gchar *shader_contents = NULL;
        gsize shader_size = 0;

        shader_load_file(s, &shader_contents, &shader_size);
        shader_compile_source(s, shader_type, shader_contents, shader_size);
        shader_monitor_file(s);
    }
    return s;
}

void
shader_compile_source(Shader      *s,
                      GLenum       shader_type,
                      const gchar *shader_contents,
                      gsize        shader_size)
{
    if (shader_contents == NULL)
    {
        shader_compiled_emit(s, FALSE);
        return;
    }

    s->shader_type = shader_type;
    s->shader_id = glCreateShader(shader_type);

    glShaderSource(s->shader_id, 1, (const GLchar **) &shader_contents,
                   (const GLint *) &shader_size);
    glCompileShader(s->shader_id);

    GLchar shader_log[GL_LOG_SIZE];
    glGetShaderInfoLog(s->shader_id, GL_LOG_SIZE, NULL, shader_log);
    printf("[INFO] - OpenGL shader log: %s\n", shader_log);

    GLint status;
    glGetShaderiv(s->shader_id, GL_COMPILE_STATUS, &status);
    if (status == GL_TRUE)
    {
        shader_compiled_emit(s, TRUE);
    }
    else
    {
        fprintf(stderr, "[FAIL] - Unable to compile shader code: %s\n", s->file_name);
        shader_compiled_emit(s, FALSE);
    }
}

gboolean
shader_find_file(Shader *s, const gchar *path)
{
    s->file = g_file_new_for_path(path);
    if (g_file_query_exists(s->file, NULL))
    {
        fprintf(stderr, "[FAIL] - Shader file does not exist: %s\n", path);
        return FALSE;
    }
    s->file_name = g_file_get_basename(s->file);
    return TRUE;
}

void
shader_load_file(Shader  *s,
                 gchar  **shader_contents,
                 gsize   *shader_size)
{
    GError *error = NULL;
    g_file_load_contents(s->file,
                         NULL, shader_contents, shader_size,
                         NULL, &error);

    if (error != NULL)
    {
        fprintf(stderr, "[FAIL] - Unable to read shader file: %s\n", error->message);
        g_error_free(error);
    }
}

void
shader_delete(Shader *s)
{
    glDeleteShader(s->shader_id);

    g_object_unref(s->file);
    g_object_unref(s->file_monitor);

    if (s->file_name != NULL)
    {
        g_free(s->file_name);
    }
    shader_compiled_emit(s, FALSE);
}

gboolean
shader_compiled(Shader *s)
{
    return s->shader_compiled;
}

gchar*
shader_file_name(Shader *s)
{
    return s->file_name;
}

GLuint
shader_id(Shader *s)
{
    return s->shader_id;
}

static void
shader_finalize(GObject *obj)
{
    shader_delete(SHADER_OBJECT(obj));

    G_OBJECT_CLASS (shader_parent_class)->finalize(obj);
}

static void
shader_class_init(ShaderClass *class)
{
    g_signal_new("shader-changed",
                 G_TYPE_FROM_CLASS(class),
                 G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE,
                 0, NULL, NULL, NULL,
                 G_TYPE_NONE, 0, NULL);

    g_signal_new("shader-compiled",
                 G_TYPE_FROM_CLASS(class),
                 G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE,
                 0, NULL, NULL, NULL,
                 G_TYPE_NONE, 1, G_TYPE_BOOLEAN);
}

static void
shader_init(Shader *s)
{
    s->file = NULL;
    s->file_monitor = NULL;
    s->file_name = NULL;

    s->shader_type = GL_FRAGMENT_SHADER;
    s->shader_id = 0;
    s->shader_compiled = FALSE;
}
