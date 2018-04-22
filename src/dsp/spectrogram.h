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

#ifndef __SPECTROGRAM_H__
#define __SPECTROGRAM_H__

#include <glib-object.h>

#include <liquid/liquid.h>

G_BEGIN_DECLS

#define SPECTROGRAM_TYPE (spectrogram_get_type ())

G_DECLARE_FINAL_TYPE (Spectrogram, spectrogram, SPECTROGRAM, OBJECT, GObject)

Spectrogram* spectrogram_new    (guint64 nfft,
                                 guint64 time_len,
                                 gint    window_type,
                                 guint64 window_len,
                                 guint64 delay,
                                 guint64 samples_per_estimate);

void         spectrogram_write  (Spectrogram         *s,
                                 const float complex *x,
                                 guint64              n);

void         spectrogram_clear  (Spectrogram *s);       
void         spectrogram_delete (Spectrogram *s);

G_END_DECLS

#endif