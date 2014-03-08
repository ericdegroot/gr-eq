INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_EQ eq)

FIND_PATH(
    EQ_INCLUDE_DIRS
    NAMES eq/api.h
    HINTS $ENV{EQ_DIR}/include
        ${PC_EQ_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    EQ_LIBRARIES
    NAMES gnuradio-eq
    HINTS $ENV{EQ_DIR}/lib
        ${PC_EQ_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(EQ DEFAULT_MSG EQ_LIBRARIES EQ_INCLUDE_DIRS)
MARK_AS_ADVANCED(EQ_LIBRARIES EQ_INCLUDE_DIRS)

