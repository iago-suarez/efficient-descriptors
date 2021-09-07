cmake_minimum_required(VERSION 3.10.2)
project(efficient-descriptors)

# Import OpenCV
find_package(OpenCV REQUIRED)
message( STATUS "OpenCV_FOUND: " ${OpenCV_FOUND})
message( STATUS "OpenCV_INCLUDE_DIRS: " ${OpenCV_INCLUDE_DIRS})
message( STATUS "OpenCV_LIBS: " ${OpenCV_LIBS})
include_directories(${OpenCV_INCLUDE_DIRS})

# Do not use parallel_for_ if OpenCV 3.X
option(PARALLEL_DESCRIPTORS "Use multiple threads to compute descriptors" ON)
if(${OpenCV_VERSION} VERSION_LESS "4.0.0")
    set(PARALLEL_DESCRIPTORS OFF)
endif()
if(PARALLEL_DESCRIPTORS)
    add_definitions(-DUPM_BAD_PARALLEL -DUPM_PARALLEL_SIFT -DUPM_PARALLEL_HASH_SIFT)
endif(PARALLEL_DESCRIPTORS)
message(STATUS "PARALLEL_DESCRIPTORS: ${PARALLEL_DESCRIPTORS}")

# Used C++ v14
set(CMAKE_CXX_STANDARD 14)

# Compile demo code
add_executable(homography_demo homography_demo.cpp BAD.cpp HashSIFT.cpp PatchSIFT.cpp)
target_link_libraries(homography_demo ${OpenCV_LIBS})

add_executable(stereo_demo stereo_demo.cpp BAD.cpp HashSIFT.cpp PatchSIFT.cpp)
target_link_libraries(stereo_demo ${OpenCV_LIBS})

# Copy images to build directory
file(COPY ${CMAKE_SOURCE_DIR}/imgs DESTINATION ${CMAKE_BINARY_DIR})