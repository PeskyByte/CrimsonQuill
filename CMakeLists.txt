cmake_minimum_required(VERSION 3.18.4)

set(NAME CrimsonQuill)
set(VERSION 0.0.1)

project(
  ${NAME}
  LANGUAGES C
  VERSION ${VERSION})

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BINARY_DIR build)
set(CMAKE_SOURCE_DIR src)

file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/*.c)
add_executable(${NAME} ${SRC_FILES})

target_include_directories(${NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
