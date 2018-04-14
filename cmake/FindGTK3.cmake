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
# GTK3_FOUND
# GTK3_INCLUDE_DIR
# GTK3_LIBRARY
#

find_package(PkgConfig REQUIRED)
PKG_CHECK_MODULES(PC_GTK3 gtk+-3.0)

set(GTK3_INCLUDE_DIR ${PC_GTK3_INCLUDE_DIRS})
set(GTK3_LIBRARIES ${PC_GTK3_LIBRARIES})

find_package_handle_standard_args(gtk3 GTK3_LIBRARY GTK3_INCLUDE_DIR)
mark_as_advanced(GTK3_INCLUDE_DIR GTK3_LIBRARY)
