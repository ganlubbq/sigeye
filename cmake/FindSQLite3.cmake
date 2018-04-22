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
# along with SigEye. If not, see <http://www.gnu.org/licenses/>.
#

#
# SQLITE3_FOUND
# SQLITE3_INCLUDE_DIR
# SQLITE3_LIBRARY
#

find_path(SQLITE3_INCLUDE_DIR sqlite3.h)
find_library(
    SQLITE3_LIBRARY NAMES sqlite3 libsqlite3
    HINTS /usr/lib /usr/local/lib
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(sqlite3 SQLITE3_LIBRARY SQLITE3_INCLUDE_DIR)
mark_as_advanced(SQLITE3_INCLUDE_DIR SQLITE3_LIBRARY)
