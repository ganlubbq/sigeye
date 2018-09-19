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

#ifndef __SAMPLE_CAPTURE_H__
#define __SAMPLE_CAPTURE_H__

#include <glib-object.h>

#include "data_types.h"

G_BEGIN_DECLS

#define SAMPLE_TYPE_CAPTURE (sample_capture_get_type ())

G_DECLARE_FINAL_TYPE (SampleCapture, sample_capture, SAMPLE, CAPTURE, GObject)

SampleCapture*    sample_capture_new           ();
SampleCapture*    sample_capture_new_from      (const gchar       *path,
                                                SampleCaptureType  sample_type);

void              sample_capture_detect_type   (SampleCapture *s,
                                                SampleCaptureType default_type);

gboolean          sample_capture_find_file     (SampleCapture *s, const gchar *path);
void              sample_capture_read_file     (SampleCapture *s);

gpointer          sample_capture_load          (SampleCapture *s,
                                                guint64        offset,
                                                guint64        requested,
                                                guint64       *actual);

guint64           sample_capture_stream_offset (SampleCapture *s);
guint64           sample_capture_sample_size   (SampleCapture *s);
guint64           sample_capture_num_samples   (SampleCapture *s);

SampleCaptureType sample_capture_type          (SampleCapture *s);

G_END_DECLS

#endif
