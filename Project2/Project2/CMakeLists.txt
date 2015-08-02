cmake_minimum_required(VERSION 2.8)

project( RPG ) # this is case sensitive
 SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
######################################
# finds OpenGL, GLU and X11
find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
    message("ERROR: OpenGL not found")
endif(NOT OPENGL_FOUND)
set(GL_LIBRARY GL GLU X11)

#MARK - GLIB
find_package(PkgConfig)
pkg_check_modules(PC_GLIB QUIET glib-2.0)

find_library(GLIB_LIBRARIES
    NAMES glib-2.0
    HINTS ${PC_GLIB_LIBDIR}
          ${PC_GLIB_LIBRARY_DIRS}
)

# Files in glib's main include path may include glibconfig.h, which,
# for some odd reason, is normally in $LIBDIR/glib-2.0/include.
get_filename_component(_GLIB_LIBRARY_DIR ${GLIB_LIBRARIES} PATH)
find_path(GLIBCONFIG_INCLUDE_DIR
    NAMES glibconfig.h
    HINTS ${PC_LIBDIR} ${PC_LIBRARY_DIRS} ${_GLIB_LIBRARY_DIR}
          ${PC_GLIB_INCLUDEDIR} ${PC_GLIB_INCLUDE_DIRS}
    PATH_SUFFIXES glib-2.0/include
)

find_path(GLIB_INCLUDE_DIR
    NAMES glib.h
    HINTS ${PC_GLIB_INCLUDEDIR}
          ${PC_GLIB_INCLUDE_DIRS}
    PATH_SUFFIXES glib-2.0
)

set(GLIB_INCLUDE_DIRS ${GLIB_INCLUDE_DIR} ${GLIBCONFIG_INCLUDE_DIR})

# Version detection
file(READ "${GLIBCONFIG_INCLUDE_DIR}/glibconfig.h" GLIBCONFIG_H_CONTENTS)
string(REGEX MATCH "#define GLIB_MAJOR_VERSION ([0-9]+)" _dummy "${GLIBCONFIG_H_CONTENTS}")
set(GLIB_VERSION_MAJOR "${CMAKE_MATCH_1}")
string(REGEX MATCH "#define GLIB_MINOR_VERSION ([0-9]+)" _dummy "${GLIBCONFIG_H_CONTENTS}")
set(GLIB_VERSION_MINOR "${CMAKE_MATCH_1}")
string(REGEX MATCH "#define GLIB_MICRO_VERSION ([0-9]+)" _dummy "${GLIBCONFIG_H_CONTENTS}")
set(GLIB_VERSION_MICRO "${CMAKE_MATCH_1}")
set(GLIB_VERSION "${GLIB_VERSION_MAJOR}.${GLIB_VERSION_MINOR}.${GLIB_VERSION_MICRO}")

# Additional Glib components.  We only look for libraries, as not all of them
# have corresponding headers and all headers are installed alongside the main
# glib ones.
foreach (_component ${GLIB_FIND_COMPONENTS})
    if (${_component} STREQUAL "gio")
        find_library(GLIB_GIO_LIBRARIES NAMES gio-2.0 HINTS ${_GLIB_LIBRARY_DIR})
        set(ADDITIONAL_REQUIRED_VARS ${ADDITIONAL_REQUIRED_VARS} GLIB_GIO_LIBRARIES)
    elseif (${_component} STREQUAL "gobject")
        find_library(GLIB_GOBJECT_LIBRARIES NAMES gobject-2.0 HINTS ${_GLIB_LIBRARY_DIR})
        set(ADDITIONAL_REQUIRED_VARS ${ADDITIONAL_REQUIRED_VARS} GLIB_GOBJECT_LIBRARIES)
    elseif (${_component} STREQUAL "gmodule")
        find_library(GLIB_GMODULE_LIBRARIES NAMES gmodule-2.0 HINTS ${_GLIB_LIBRARY_DIR})
        set(ADDITIONAL_REQUIRED_VARS ${ADDITIONAL_REQUIRED_VARS} GLIB_GMODULE_LIBRARIES)
    elseif (${_component} STREQUAL "gthread")
        find_library(GLIB_GTHREAD_LIBRARIES NAMES gthread-2.0 HINTS ${_GLIB_LIBRARY_DIR})
        set(ADDITIONAL_REQUIRED_VARS ${ADDITIONAL_REQUIRED_VARS} GLIB_GTHREAD_LIBRARIES)
    elseif (${_component} STREQUAL "gio-unix")
        # gio-unix is compiled as part of the gio library, but the include paths
        # are separate from the shared glib ones. Since this is currently only used
        # by WebKitGTK+ we don't go to extraordinary measures beyond pkg-config.
        pkg_check_modules(GIO_UNIX QUIET gio-unix-2.0)
    endif ()
endforeach ()

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GLIB REQUIRED_VARS GLIB_INCLUDE_DIRS GLIB_LIBRARIES ${ADDITIONAL_REQUIRED_VARS}
                                       VERSION_VAR   GLIB_VERSION)

mark_as_advanced(
    GLIBCONFIG_INCLUDE_DIR
    GLIB_GIO_LIBRARIES
    GLIB_GIO_UNIX_LIBRARIES
    GLIB_GMODULE_LIBRARIES
    GLIB_GOBJECT_LIBRARIES
    GLIB_GTHREAD_LIBRARIES
    GLIB_INCLUDE_DIR
    GLIB_INCLUDE_DIRS
    GLIB_LIBRARIES
)


#MARK - PANGO
if (Pango_1_0_INCLUDE_DIR)
  # Already in cache, be silent
  set(Pango_1_0_FIND_QUIETLY TRUE)
endif (Pango_1_0_INCLUDE_DIR)

find_path(Pango_1_0_INCLUDE_DIR pango/pango.h
  /opt/local/include
  /usr/local/include
  /usr/include
  /opt/local/include/pango-1.0
  /usr/local/include/pango-1.0
  /usr/include/pango-1.0
)

set(Pango_1_0_NAMES pango-1.0)
find_library(Pango_1_0_LIBRARY
  NAMES ${Pango_1_0_NAMES}
  PATHS /usr/lib /usr/local/lib /opt/local/lib
)

if (Pango_1_0_INCLUDE_DIR AND Pango_1_0_LIBRARY)
   set(Pango_1_0_FOUND TRUE)
   set( Pango_1_0_LIBRARIES ${Pango_1_0_LIBRARY} )
else (Pango_1_0_INCLUDE_DIR AND Pango_1_0_LIBRARY)
   set(Pango_1_0_FOUND FALSE)
   set(Pango_1_0_LIBRARIES)
endif (Pango_1_0_INCLUDE_DIR AND Pango_1_0_LIBRARY)

if (Pango_1_0_FOUND)
   if (NOT Pango_1_0_FIND_QUIETLY)
      message(STATUS "Found Pango_1_0: ${Pango_1_0_LIBRARY}")
   endif (NOT Pango_1_0_FIND_QUIETLY)
else (Pango_1_0_FOUND)
   if (Pango_1_0_FIND_REQUIRED)
      message(STATUS "Looked for Pango_1_0 libraries named ${Pango_1_0_NAMES}.")
      message(STATUS "Include file detected: [${Pango_1_0_INCLUDE_DIR}].")
      message(STATUS "Lib file detected: [${Pango_1_0_LIBRARY}].")
      message(FATAL_ERROR "=========> Could NOT find Pango_1_0 library")
   endif (Pango_1_0_FIND_REQUIRED)
endif (Pango_1_0_FOUND)

mark_as_advanced(
  Pango_1_0_LIBRARY
  Pango_1_0_INCLUDE_DIR
  )

#MARK - cario
IF(Cairo_FIND_REQUIRED)
	SET(_pkgconfig_REQUIRED "REQUIRED")
ELSE(Cairo_FIND_REQUIRED)
	SET(_pkgconfig_REQUIRED "")
ENDIF(Cairo_FIND_REQUIRED)

IF(CAIRO_MIN_VERSION)
	PKG_SEARCH_MODULE(CAIRO ${_pkgconfig_REQUIRED} cairo>=${CAIRO_MIN_VERSION})
ELSE(CAIRO_MIN_VERSION)
	PKG_SEARCH_MODULE(CAIRO ${_pkgconfig_REQUIRED} cairo)
ENDIF(CAIRO_MIN_VERSION)

IF(NOT CAIRO_FOUND AND NOT PKG_CONFIG_FOUND)
	FIND_PATH(CAIRO_INCLUDE_DIRS cairo.h)
	FIND_LIBRARY(CAIRO_LIBRARIES cairo)

	# Report results
	IF(CAIRO_LIBRARIES AND CAIRO_INCLUDE_DIRS)
		SET(CAIRO_FOUND 1)
		IF(NOT Cairo_FIND_QUIETLY)
			MESSAGE(STATUS "Found Cairo: ${CAIRO_LIBRARIES}")
		ENDIF(NOT Cairo_FIND_QUIETLY)
	ELSE(CAIRO_LIBRARIES AND CAIRO_INCLUDE_DIRS)
		IF(Cairo_FIND_REQUIRED)
			MESSAGE(SEND_ERROR "Could not find Cairo")
		ELSE(Cairo_FIND_REQUIRED)
			IF(NOT Cairo_FIND_QUIETLY)
				MESSAGE(STATUS "Could not find Cairo")
			ENDIF(NOT Cairo_FIND_QUIETLY)
		ENDIF(Cairo_FIND_REQUIRED)
	ENDIF(CAIRO_LIBRARIES AND CAIRO_INCLUDE_DIRS)
ENDIF(NOT CAIRO_FOUND AND NOT PKG_CONFIG_FOUND)

# Hide advanced variables from CMake GUIs
MARK_AS_ADVANCED(CAIRO_LIBRARIES CAIRO_INCLUDE_DIRS)

#MARK GTK
FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-2.0)

# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})

# Add other flags to the compiler
ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})

#MARK SOIL
IF (SOIL_INCLUDE_DIR)
  # Already in cache, be silent
  SET(SOIL_FIND_QUIETLY TRUE)
ENDIF (SOIL_INCLUDE_DIR)

FIND_PATH(SOIL_INCLUDE_DIR SOIL.h PATH_SUFFIXES include/SOIL include)

SET(SOIL_NAMES SOIL Soil soil)
FIND_LIBRARY(SOIL_LIBRARY NAMES ${SOIL_NAMES} )
MARK_AS_ADVANCED( SOIL_LIBRARY SOIL_INCLUDE_DIR )

# Per-recommendation
SET(SOIL_INCLUDE_DIRS "${SOIL_INCLUDE_DIR}")
SET(SOIL_LIBRARIES    "${SOIL_LIBRARY}")

# handle the QUIETLY and REQUIRED arguments and set SOIL_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(SOIL DEFAULT_MSG SOIL_LIBRARIES SOIL_INCLUDE_DIRS)

# linking "glfw" and not "glfw3"
# assumes that glfw was built with BUILD_SHARED_LIBS to ON
include_directories(kal ${Pango_1_0_INCLUDE_DIR} ${GLIB_INCLUDE_DIR} ${GLIBCONFIG_INCLUDE_DIR} ${CAIRO_INCLUDE_DIRS})
add_executable(kal main.cpp)
target_link_libraries(kal glfw  ${GL_LIBRARY} ${Pango_1_0_LIBRARY} ${GLIB_LIBRARIES} ${GTK3_LIBRARIES} ${SOIL_LIBRARIES} m)
