cmake_minimum_required (VERSION 2.6)
project (lecture_matmul)

list (APPEND CMAKE_CXX_FLAGS "-std=c++11 -Wall")

set (LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory (src)

enable_testing ()
add_subdirectory (test)

install (DIRECTORY ${PROJECT_SOURCE_DIR}/include/
  DESTINATION include)
