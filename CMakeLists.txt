# v3.14 required for FetchContent_MakeAvailable
cmake_minimum_required(VERSION 3.14)
# Project information
project(Wmm2020
  VERSION 1.0.0
  DESCRIPTION "World Magnetic Model 2020"
  LANGUAGES CXX
)
include(FetchContent)
# Fetch units
FetchContent_Declare(
  units
  GIT_REPOSITORY https://github.com/bolderflight/units.git
  GIT_TAG	v4.2.1
)
FetchContent_MakeAvailable(units)
# Add the library target
add_library(wmm
  src/wmm.cpp
)
target_link_libraries(wmm
  PRIVATE
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
