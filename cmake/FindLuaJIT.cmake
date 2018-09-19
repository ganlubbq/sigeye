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
# LUAJIT_FOUND
# LUAJIT_INCLUDE_DIR
# LUAJIT_LIBRARY
#

find_path(
    LUAJIT_INCLUDE_DIR luajit.h
    PATH_SUFFIXES include include/luajit include/luajit-2.1
)
find_library(
    LUAJIT_LIBRARY NAMES luajit luajit-5.1 libluajit libluajit-5.1
    HINTS /usr/lib /usr/local/lib /usr/lib/x86_64-linux-gnu
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(luajit LUAJIT_LIBRARY LUAJIT_INCLUDE_DIR)
mark_as_advanced(LUAJIT_INCLUDE_DIR LUAJIT_LIBRARY)
