cmake_minimum_required(VERSION 3.30)

project("GL" VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS Src/*.cpp)
file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS Inc/*.hpp)

add_compile_options(-Wall -Wextra -Wpedantic -Werror)
add_executable(${CMAKE_PROJECT_NAME} ${SRC_FILES})

find_package(glfw3 3.4 REQUIRED)
find_package(GLEW REQUIRED)

target_precompile_headers(${CMAKE_PROJECT_NAME} PUBLIC "Inc/Gl.hpp")
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Inc ${GLEW_INCLUDE_DIRS})
target_link_libraries(${CMAKE_PROJECT_NAME} glfw GLEW::GLEW)

if(APPLE)
  target_link_libraries(${CMAKE_PROJECT_NAME} "-framework Cocoa" "-framework IOKit")
endif()
