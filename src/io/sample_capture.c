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

#include "sample_capture.h"

#include <gio/gio.h>

#include <stdio.h>

struct _SampleCapture
{
    GFile* file;

    GFileMonitor* file_monitor;

    GFileInputStream* file_stream;

    gchar* file_name;
    gchar* file_path;

    SampleCaptureType sample_type;

    guint64 stream_offset;
    guint64 sample_size;
    guint64 num_samples;
};

G_DEFINE_TYPE (SampleCapture, sample_capture, G_TYPE_OBJECT)

static void
sample_capture_changed_emit(SampleCapture *s)
{
    g_signal_emit_by_name(s, "capture-changed", NULL);
}

static void
sample_capture_changed_cb(GFileMonitor     *file_monitor,
                          GFile            *file,
                          GFile            *other_file,
                          GFileMonitorEvent event_type,
                          gpointer          user_data)
{
    SampleCapture *s = SAMPLE_CAPTURE(user_data);

    sample_capture_changed_emit(s);

    sample_capture_data_type(s, COMPLEX_FLOAT_32);
    sample_capture_read_file(s);
}

static void
sample_capture_monitor_file(SampleCapture *s)
{
    s->file_monitor = g_file_monitor_file(s->file,
                                          G_FILE_MONITOR_WATCH_MOVES,
                                          NULL, NULL);
    if (s->file_monitor == NULL)
    {
        fprintf(stderr, "[FAIL] - Unable to monitor sample capture file: %s\n", s->file_name);
        return;
    }

    g_signal_connect(s->file_monitor, "changed", G_CALLBACK(sample_capture_changed_cb), s);
}

SampleCapture*
sample_capture_new()
{
    return g_object_new(SAMPLE_TYPE_CAPTURE, NULL);
}

void
sample_capture_data_type(SampleCapture *s,
                         SampleCaptureType default_type)
{
}

SampleCapture*
sample_capture_new_from(const gchar       *path,
                        SampleCaptureType  sample_type)
{
    SampleCapture *s = sample_capture_new();
    if (sample_capture_find_file(s, path))
    {
        sample_capture_data_type(s, sample_type);
        sample_capture_read_file(s);
        sample_capture_monitor_file(s);
    }
    return s;
}

gboolean
sample_capture_find_file(SampleCapture *s, const gchar *path)
{
    s->file = g_file_new_for_path(path);
    if (!g_file_query_exists(s->file, NULL))
    {
        fprintf(stderr, "[FAIL] - Sample capture does not exist: %s\n", path);
        return FALSE;
    }
    s->file_name = g_file_get_basename(s->file);
    s->file_path = g_file_get_path(s->file);
    return TRUE;
}

static void
sample_capture_read_cb(GObject      *source_object,
                       GAsyncResult *result,
                       gpointer      user_data)
{
    GFile *file = G_FILE(source_object);

    SampleCapture *s = SAMPLE_CAPTURE(user_data);

    GError *error = NULL;

    s->file_stream = g_file_read_finish(file, result, &error);

    if (error != NULL)
    {
        fprintf(stderr, "[FAIL] - Unable to read sample capture: %s\n", error->message);
        g_error_free(error);
    }
}

void
sample_capture_read_file(SampleCapture *s)
{
    g_file_read_async(s->file,
                      G_PRIORITY_DEFAULT,
                      NULL,
                      sample_capture_read_cb,
                      s);
}

gpointer
sample_capture_load(SampleCapture *s,
                    guint64        offset,
                    guint64        requested,
                    guint64       *actual)
{

}

guint64
sample_capture_stream_offset(SampleCapture *s)
{
    return s->stream_offset;
}

guint64
sample_capture_sample_size(SampleCapture *s)
{
    return s->sample_size;
}

guint64
sample_capture_num_samples(SampleCapture *s)
{
    return s->num_samples;
}

SampleCaptureType
sample_capture_type(SampleCapture *s)
{
    return s->sample_type;
}

static void
sample_capture_finalize(GObject *obj)
{
    G_OBJECT_CLASS (sample_capture_parent_class)->finalize(obj);
}

static void
sample_capture_class_init(SampleCaptureClass *class)
{
    g_signal_new("capture-changed",
                 G_TYPE_FROM_CLASS(class),
                 G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE,
                 0, NULL, NULL, NULL,
                 G_TYPE_NONE, 0, NULL);
}

static void
sample_capture_init(SampleCapture *s)
{
    s->file = NULL;
    s->file_monitor = NULL;
    s->file_stream = NULL;
    s->file_name = NULL;
    s->file_path = NULL;

    s->stream_offset = 0;
    s->sample_size = 0;
    s->num_samples = 0;
}
