#
# This file is part of SigEye.
#
# SigEye is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# SigEye is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with SigEye.  If not, see <http://www.gnu.org/licenses/>.
#

#
# FFTW_FOUND
# FFTW_INCLUDE_DIR
# FFTW_LIBRARY
#

find_path(FFTW_INCLUDE_DIR fftw3.h)
find_library(FFTW_LIBRARY NAMES fftw3)

find_package_handle_standard_args(fftw3 FFTW_LIBRARY FFTW_INCLUDE_DIR)
mark_as_advanced(FFTW_INCLUDE_DIR FFTW_LIBRARY)
