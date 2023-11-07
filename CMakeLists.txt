cmake_minimum_required(VERSION 3.5)  # Or whatever minimum version you choose
project(LungModelling)


if(COMMAND CMAKE_POLICY)
  CMAKE_POLICY(SET CMP0003 NEW)
endif()

if(NOT IS_SUBBUILD)
  set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake;${CMAKE_MODULE_PATH};")
else()
  set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/CMake")
endif()

# Use full RPATH
set(CMAKE_SKIP_BUILD_RPATH  FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

# Set RPATH/INSTALL_NAME_DIR for installation
if (NOT APPLE)
  set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib:\$ORIGIN/../lib")
else()
  set(CMAKE_INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib")
endif()

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

# Set directory variables
set(BIN_DIR bin CACHE STRING "Binary directory")
set(LIB_DIR lib CACHE STRING "Library directory")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Set library paths
set(EIGEN_CUSTOM_INCLUDE_DIR /opt/homebrew/Cellar/eigen/3.4.0_1/include/eigen3 CACHE PATH "Eigen Include Directory")
set(CGAL_CUSTOM_ROOT_DIR /opt/homebrew/Cellar/cgal/5.6 CACHE PATH "CGAL Root Directory")
set(ITK_DIR /opt/homebrew/Cellar/itk/5.3.0_2.reinstall CACHE PATH "ITK Directory")
set(BOOST_ROOT /opt/homebrew/Cellar/boost/1.83.0 CACHE PATH "Boost Root Directory")
set(VTK_DIR /opt/homebrew/Cellar/vtk/9.2.6_5 CACHE PATH "VTK Directory")
ADD_DEFINITIONS(-D_SOLUTIONPATH=\"${CMAKE_SOURCE_DIR}\")

# Find necessary packages
find_package(OpenMP)
find_package(OpenGL)
find_package(CGAL REQUIRED)
find_package(ITK REQUIRED)
# Add more find_package commands for other libraries if necessary

# Set compiler flags for OpenMP if found
if (OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

# Add subdirectories
add_subdirectory(src)
