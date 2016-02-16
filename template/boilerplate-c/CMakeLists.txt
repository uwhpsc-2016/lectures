cmake_minimum_required (VERSION 2.6)
project (lecture)

list (APPEND CMAKE_C_FLAGS "-Wall")

set (LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory (src)
add_subdirectory (test)

install (DIRECTORY ${PROJECT_SOURCE_DIR}/include/
  DESTINATION include)
