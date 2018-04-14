#
# This file is part of SigEye.
#
# SigCat is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# SigCat is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with SigEye.  If not, see <http://www.gnu.org/licenses/>.
#

#########################
# Project configuration #
#########################
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(sigeye C)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_BUILD_TYPE Debug)

#####################
# Project libraries #
#####################
find_package(Threads REQUIRED)
find_package(FFTW    REQUIRED)
find_package(GTK3    REQUIRED)

##############################
# Include source directories #
##############################
list(APPEND PROJECT_INCLUDES src)
list(APPEND PROJECT_INCLUDES ${FFTW_INCLUDE_DIR})

include_directories(${PROJECT_INCLUDES})

###########################
# Project sub-directories #
###########################
add_subdirectory(src)
