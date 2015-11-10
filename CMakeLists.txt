cmake_minimum_required(VERSION 2.8.7)
project(HeightMapCreator)
set(EXECUTABLE "HeightMapCreator")

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)

# Includes
include_directories(
    ${PROJECT_SOURCE_DIR}
    "include/terragen_file_manager"
)

link_directories(
    ${PROJECT_SOURCE_DIR}
    "lib/"
)

SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -O2 -g -DGL_DEBUG -std=c++11")
SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -std=c++11")
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -DGL_DEBUG -std=c++11")
SET(CMAKE_BUILD_TYPE RELWITHDEBINFO)
#SET(CMAKE_VERBOSE_MAKEFILE true )
SET(SOURCE_FILES main_window main central_widget form_row png_file terragen_file_parser img_file pixel heightmap_file utils
terragen_heightmap_wrapper lodepng/lodepng)

#add_subdirectory(lodepng)

add_executable(${EXECUTABLE} ${SOURCE_FILES} ${RESOURCES})
# Use the Widgets module from Qt 5.
target_link_libraries(${EXECUTABLE} Qt5::Widgets Qt5::Core Qt5::Gui TerragenFileManager)
