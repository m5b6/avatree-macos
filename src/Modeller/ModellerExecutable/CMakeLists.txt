cmake_minimum_required(VERSION 2.8)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR} CACHE TYPE PATH)
set(CXX_STANDARD 17)

project(ModellerCMD)

file(GLOB MODELLEREXEC_SRC
)

FOREACH(MODELLEREXEC_SRC ${MODELLEREXEC_SRC})
    MESSAGE(STATUS "Process file: ${MODELLEREXEC_SRC}")
ENDFOREACH(MODELLEREXEC_SRC)
file(GLOB MODELLEREXEC_SRC
    "_main.cpp"
    "../Modeller/include/*.h"
    "../Modeller/*.cpp"
)

add_compile_definitions(BOOST_ALL_NO_LIB)
add_definitions(${PCL_DEFINITIONS})
set(EIGEN_CUSTOM_INCLUDE_DIR /opt/homebrew/Cellar/eigen/3.4.0_1/include/eigen3 CACHE PATH "Eigen Include Directory")
set(BOOST_ROOT /opt/homebrew/Cellar/boost/1.83.0 CACHE PATH "Boost Root Directory")
set(Boost_INCLUDE_DIRS /opt/homebrew/Cellar/boost/1.83.0/include CACHE PATH "Boost Include Directory")
set(CGAL_CUSTOM_ROOT_DIR /opt/homebrew/Cellar/cgal/5.6 CACHE PATH "CGAL Root Directory")
set(MPFR_ROOT_DIR /opt/homebrew/Cellar/mpfr/4.2.0-p12)
set(GMP_ROOT_DIR /opt/homebrew/Cellar/gmp/6.3.0)

# Find ITK
find_package(ITK REQUIRED)
find_package(TIFF REQUIRED)
find_package(CGAL REQUIRED)

include(${ITK_USE_FILE})
include_directories(${TIFF_INCLUDE_DIRS})


# Include Directories
include_directories(
    ${CMAKE_SOURCE_DIR}/../Modeller/include 
    ${CMAKE_SOURCE_DIR}/../Modeller/ 
    ${CMAKE_SOURCE_DIR}/../ 
    ${CMAKE_SOURCE_DIR}/include/OpenGL
	"/Users/mb/Desktop/repos/other/avatree/src/Modeller/Modeller/"
	"/Users/mb/Desktop/repos/other/avatree/src/Modeller/Modeller/include"
	${CGAL_CUSTOM_ROOT_DIR}/auxiliary/gmp/include
    ${CGAL_CUSTOM_ROOT_DIR}/include
    ${EIGEN_CUSTOM_INCLUDE_DIR}
    ${Boost_INCLUDE_DIRS}
    ${PCL_INCLUDE_DIRS}
	${ITK_INCLUDE_DIRS}
)

# Link Directories
link_directories(
	"/opt/homebrew/Cellar/libtiff/4.6.0/lib"
	"/opt/homebrew/lib/"
    ${CMAKE_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/lib
    ${CGAL_CUSTOM_ROOT_DIR}/lib
    ${CGAL_CUSTOM_ROOT_DIR}/auxiliary/gmp/lib
    ${Boost_LIBRARY_DIR}
    ${Boost_DIR}/../../
)



set(AUX_LIBRARIES ${MPFR_ROOT_DIR}/lib/libmpfr.dylib  ${ITK_LIBRARIES} ${GMP_ROOT_DIR}/lib/libgmp.dylib)

add_executable(ModellerCMD ${MODELLEREXEC_SRC})
set_target_properties(ModellerCMD PROPERTIES PROJECT_LABEL "ModellerCMD" FOLDER "CMD")
target_link_libraries(ModellerCMD ${TIFF_LIBRARIES})

target_link_libraries(ModellerCMD ${AUX_LIBRARIES} ${Boost_LIBRARIES} ${ITK_LIBRARIES} ${PCL_COMMON_LIBRARIES} ${PCL_IO_LIBRARIES} ${PCL_VISUALIZATION_LIBRARIES} ${PCL_SURFACE_LIBRARIES} ${PCL_FILTERS_LIBRARIES} ${PCL_FEATURES_LIBRARIES})
