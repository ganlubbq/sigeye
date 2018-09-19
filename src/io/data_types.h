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

#ifndef __DATA_TYPES_H__
#define __DATA_TYPES_H__

#include <glib-object.h>

#define DEFINE_COMPLEX_TYPE(TYPE, NAME)  \
    typedef struct                       \
    {                                    \
        TYPE real;                       \
        TYPE imag;                       \
    }                                    \
    NAME;

typedef enum
{
    COMPLEX_FLOAT_32 = 0,
    COMPLEX_INT_32,
    COMPLEX_INT_16,
    COMPLEX_INT_8,
    COMPLEX_UINT_32,
    COMPLEX_UINT_16,
    COMPLEX_UINT_8,
    REAL_FLOAT_32,
    REAL_INT_32,
    REAL_INT_16,
    REAL_INT_8,
    REAL_UINT_32,
    REAL_UINT_16,
    REAL_UINT_8
}
SampleCaptureType;

DEFINE_COMPLEX_TYPE (gfloat, complex_float_32);
DEFINE_COMPLEX_TYPE (gint32, complex_int_32);
DEFINE_COMPLEX_TYPE (gint16, complex_int_16);
DEFINE_COMPLEX_TYPE (gint8, complex_int_8);
DEFINE_COMPLEX_TYPE (guint32, complex_uint_32);
DEFINE_COMPLEX_TYPE (guint16, complex_uint_16);
DEFINE_COMPLEX_TYPE (guint8, complex_uint_8);

#endif
