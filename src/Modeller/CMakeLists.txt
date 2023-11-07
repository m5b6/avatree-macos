cmake_minimum_required(VERSION 2.8.11)
set(CMAKE_CXX_STANDARD 11)
add_subdirectory(Modeller)
add_subdirectory(ModellerExecutable)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Modeller/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/Modeller/include)


#add_subdirectory(ModelFeatureGeneration)
##########################################################################################


