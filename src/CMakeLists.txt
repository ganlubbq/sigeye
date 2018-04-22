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

#############################################
# CMake functions for source subdirectories #
#############################################
function(prepend_sources RETURN_VALUE PREFIX SOURCES)
    foreach(FILE ${SOURCES})
        list(APPEND RESULT "${PREFIX}/${FILE}")
    endforeach(FILE)
    set(${RETURN_VALUE} "${RESULT}" PARENT_SCOPE)
endfunction(prepend_sources)

macro(aggregate_sources)
    prepend_sources(LOCAL_SOURCES ${CMAKE_CURRENT_SOURCE_DIR} "${ARGN}")
    list(APPEND MAIN_SOURCES ${LOCAL_SOURCES})
    set(MAIN_SOURCES ${MAIN_SOURCES} PARENT_SCOPE)
endmacro(aggregate_sources)

#############################
# Add the main source files #
#############################
list(APPEND MAIN_SOURCES
    sigeye.c
    sigeye_noodle.c
)

##################################
# Add sub directory source files #
##################################
add_subdirectory(graphics)
add_subdirectory(dsp)
add_subdirectory(io)

#######################
# Add the gl3w source #
#######################
set(GL3W_SOURCES GL/gl3w.c)

##############################
# Aggregate libraries to use #
##############################
set(CMAKE_STANDARD_LIBS m)

list(APPEND MAIN_LIBRARIES
    ${CMAKE_THREAD_LIBS_INIT}
    ${CMAKE_DL_LIBS}
    ${CMAKE_STANDARD_LIBS}
    ${FFTW_LIBRARY}
    ${LIQUID_LIBRARY}
    ${SQLITE3_LIBRARY}
    ${GTK3_LIBRARY}
)

#########################
# Build the main binary #
#########################
add_executable(sigeye ${MAIN_SOURCES} ${GL3W_SOURCES})
target_link_libraries(sigeye ${MAIN_LIBRARIES})
