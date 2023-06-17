# v3.14 required for FetchContent_MakeAvailable
cmake_minimum_required(VERSION 3.14)
# Project information
project(Wmm
  VERSION 1.1.0
  DESCRIPTION "World Magnetic Model"
  LANGUAGES CXX
)
include(FetchContent)
if (DEFINED DEPS)
  string(TOUPPER ${DEPS} DEPS)
  if (DEPS STREQUAL "BFS")
    # Fetch global defs
    FetchContent_Declare(
      units
      GIT_REPOSITORY git@192.168.1.11:bolderflight/software/units.git
      GIT_TAG v5.0.0
    )
  elseif(DEPS STREQUAL "LOCAL")
    # Fetch global defs
    FetchContent_Declare(
      units
      GIT_REPOSITORY ${CMAKE_SOURCE_DIR}/../units
      GIT_TAG v5.0.0
    )
  else()
    # Fetch global defs
    FetchContent_Declare(
      units
      GIT_REPOSITORY https://github.com/bolderflight/units.git
      GIT_TAG v5.0.0
    )
  endif()
else()
# Fetch global defs
FetchContent_Declare(
  units
  GIT_REPOSITORY https://github.com/bolderflight/units.git
  GIT_TAG v5.0.0
)
endif()
FetchContent_MakeAvailable(units)
# Add the library target
add_library(wmm
  src/wmm.h
  src/wmm.cpp
  src/XYZgeomag.h
)
target_link_libraries(wmm
  PUBLIC
    units
)
# Setup include directories 
target_include_directories(wmm PUBLIC 
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
  $<INSTALL_INTERFACE:include>
)
# Example and test if this project is built separately
if (PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
  # Add the  example target
  add_executable(wmm_example examples/cmake/wmm_ex.cc)
  # Add the includes
  target_include_directories(wmm_example PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  )
  # Link libraries to the example target
  target_link_libraries(wmm_example
    PRIVATE
      wmm
  )
endif()
