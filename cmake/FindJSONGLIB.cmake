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
# JSONGLIB_FOUND
# JSONGLIB_INCLUDE_DIR
# JSONGLIB_LIBRARY
#

find_path(JSONGLIB_INCLUDE_DIR
    NAMES json-glib/json-glib.h
    PATH_SUFFIXES json-glib-1.0
)
find_library(JSONGLIB_LIBRARY
    NAMES json-glib json-glib-1.0
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(json-glib JSONGLIB_LIBRARY JSONGLIB_INCLUDE_DIR)
mark_as_advanced(JSONGLIB_INCLUDE_DIR JSONGLIB_LIBRARY)
