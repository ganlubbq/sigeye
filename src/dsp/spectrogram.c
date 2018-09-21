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

#include "spectrogram.h"

#include <stdlib.h>
#include <string.h>

struct _Spectrogram
{
    spgramcf spgram;

    windowf window;

    guint64 nfft;
    guint64 time_len;
    guint64 samples_per_estimate;

    gfloat* psd_result;
};

G_DEFINE_TYPE (Spectrogram, spectrogram, G_TYPE_OBJECT)

static void
spectrogram_write_emit(Spectrogram *s)
{
    g_signal_emit_by_name(s, "spectrogram-write", NULL);
}

Spectrogram*
spectrogram_new(guint64 nfft,
                guint64 time_len,
                gint    window_type,
                guint64 window_len,
                guint64 delay,
                guint64 samples_per_estimate)
{
    Spectrogram *s = g_object_new(SPECTROGRAM_TYPE, NULL);

    s->spgram = spgramcf_create(nfft, window_type, window_len, delay);
    s->window = windowf_create(nfft * time_len);

    s->nfft = nfft;
    s->time_len = time_len;
    s->samples_per_estimate = samples_per_estimate;

    s->psd_result = malloc(nfft * sizeof(gfloat));

    return s;
}

void
spectrogram_write(Spectrogram                *s,
                  const liquid_float_complex *x,
                  guint64                     n)
{
    spgramcf_write(s->spgram, (float complex *) x, n);
    if (spgramcf_get_num_samples(s->spgram) > s->samples_per_estimate)
    {
        spgramcf_get_psd(s->spgram, s->psd_result);
        spgramcf_clear(s->spgram);

        windowf_write(s->window, s->psd_result, s->nfft);

        spectrogram_write_emit(s);
    }
}

void
spectrogram_clear(Spectrogram *s)
{
    spgramcf_reset(s->spgram);
    windowf_reset(s->window);

    memset(s->psd_result, 0, s->nfft * sizeof(gfloat));
}

void
spectrogram_delete(Spectrogram *s)
{
    spgramcf_destroy(s->spgram);
    windowf_destroy(s->window);

    free(s->psd_result);
}

static void
spectrogram_finalize(GObject *obj)
{
    spectrogram_delete(SPECTROGRAM_OBJECT(obj));

    G_OBJECT_CLASS (spectrogram_parent_class)->finalize(obj);
}

static void
spectrogram_class_init(SpectrogramClass *class)
{
    g_signal_new("spectrogram-write",
                 G_TYPE_FROM_CLASS(class),
                 G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE,
                 0, NULL, NULL, NULL,
                 G_TYPE_NONE, 0, NULL);
}

static void
spectrogram_init(Spectrogram *s)
{
    s->spgram = NULL;
    s->window = NULL;

    s->nfft = 0;
    s->time_len = 0;
    s->samples_per_estimate = 0;

    s->psd_result = NULL;
}