if(NOT PKG_CONFIG_FOUND)
    INCLUDE(FindPkgConfig)
endif()
PKG_CHECK_MODULES(PC_DEMONSTRATOR demonstrator)

FIND_PATH(
    DEMONSTRATOR_INCLUDE_DIRS
    NAMES demonstrator/api.h
    HINTS $ENV{DEMONSTRATOR_DIR}/include
        ${PC_DEMONSTRATOR_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    DEMONSTRATOR_LIBRARIES
    NAMES gnuradio-demonstrator
    HINTS $ENV{DEMONSTRATOR_DIR}/lib
        ${PC_DEMONSTRATOR_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/demonstratorTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(DEMONSTRATOR DEFAULT_MSG DEMONSTRATOR_LIBRARIES DEMONSTRATOR_INCLUDE_DIRS)
MARK_AS_ADVANCED(DEMONSTRATOR_LIBRARIES DEMONSTRATOR_INCLUDE_DIRS)
