cmake_minimum_required(VERSION 2.8)
# Project Name
PROJECT(Glut-Test)

find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)

set( SOURCE
  ${SRC_DIR}/game.cpp
  ${SRC_DIR}/field.cpp
  ${SRC_DIR}/tile.cpp
  ${SRC_DIR}/util.cpp
  ${SRC_DIR}/vec2.cpp
  ${SRC_DIR}/position.cpp
)

include_directories(
  ${PROJECT_SOURCE_DIR}/include
)

set( CMAKE_CXX_FLAGS "-O0 -Wall ")

add_executable( hexgame ${SOURCE})

include_directories(${OpenGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

target_link_libraries(hexgame ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
if( UNIX)
  install( TARGETS hexgame DESTINATION ~/bin)
endif( UNIX)
