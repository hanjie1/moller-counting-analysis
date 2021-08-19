#----------------------------------------------------------------------------
# Setup the project
#
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(GenRoot)

# Default install path is the source directory
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    message(STATUS "    Install-prefix was at default -> forcing it to the source-dir" )
    message(STATUS "    Use -DCMAKE_INSTALL_PREFIX=/usr/local to set to something else" )
    set (CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}"
        CACHE PATH "default install path" FORCE )
endif()

# Use GNU install dirs
include(GNUInstallDirs)

list(APPEND CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")

message(STATUS  "!!! project path: ${PROJECT_SOURCE_DIR}")
message(STATUS  "!!! project path: ${REMOLL_USE_FILE}")
find_package(Remoll REQUIRED HINTS "${PROJECT_SOURCE_DIR}/../remoll")
#find_package(Remoll REQUIRED HINTS "${PROJECT_SOURCE_DIR}/../remoll/cmake/scripts")
include(${REMOLL_USE_FILE})
list(APPEND CMAKE_INSTALL_RPATH "${REMOLL_LIBRARY_DIR}")

#list(APPEND CMAKE_INSTALL_RPATH "${REMOLL_LIBRARY_DIR}/../remoll")

message(STATUS  "!!! remoll path: ${REMOLL_LIBRARY_DIR}    ${REMOLL_USE_FILE}")

find_package(ROOT REQUIRED)
include(${ROOT_USE_FILE})
list(APPEND CMAKE_INSTALL_RPATH "${ROOT_LIBRARY_DIR}")


#----------------------------------------------------------------------------
# generate dictionaries
#
ROOT_GENERATE_DICTIONARY(
    GenRootDict                         # path to dictionary to generate
    "include/GenRoottypes.h"           # list of classes to process
    LINKDEF "include/GenRootLinkDef.h"  # ROOT linkDef file
    OPTIONS -p
)

#----------------------------------------------------------------------------
#
include_directories(${PROJECT_SOURCE_DIR}/include ${REMOLL_INCLUDE_DIR})

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/GenRoot*.C)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/GenRoot*.h)
message(STATUS  "!!! include path: ${headers}")

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
#----------------------------------------------------------------------------
# Generate dictionaries as well (so we can write objects to ROOT files
#
add_library(GenRoot-lib SHARED ${sources} ${headers} GenRootDict.cxx)
set_target_properties(GenRoot-lib PROPERTIES OUTPUT_NAME GenRoot)
target_link_libraries(GenRoot-lib ${ROOT_LIBRARIES} ${REMOLL_LIBRARIES})

add_executable(GenRoot-bin GenRoot.C)
set_target_properties(GenRoot-bin PROPERTIES OUTPUT_NAME GenRoot)
target_link_libraries(GenRoot-bin ${REMOLL_LIBRARIES} GenRoot-lib)

#----------------------------------------------------------------------------
#
add_custom_target(GenRoot DEPENDS GenRoot-bin)

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS GenRoot-bin DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS GenRoot-lib DESTINATION ${CMAKE_INSTALL_LIBDIR})
