cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Project Name
PROJECT(Hex-Game)

set (CMAKE_CXX_STANDARD 17)

find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)

find_program(CLANG_TIDY
        NAMES "clang-tidy")
if (NOT CLANG_TIDY)
    message(STATUS "clang-tidy not found!")
else()
    message(STATUS "clang-tidy found: ${CLANG_TIDY}")
    set(CLANG_TIDY_COMMAND
            "${CLANG_TIDY}" -checks=-*,bugprone-*,cert-*,clang-*,cppcoreguidelines-*,modernize-*,performance-*,readability-* -header-filter='^include')
endif()

#add_subdirectory(glm)

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)

set( SOURCE
  ${SRC_DIR}/game.cpp
  ${SRC_DIR}/field.cpp
  ${SRC_DIR}/player.cpp
  ${SRC_DIR}/tile.cpp
  ${SRC_DIR}/util.cpp
  ${SRC_DIR}/gui.cpp
  ${SRC_DIR}/button.cpp
)

set( CMAKE_CXX_FLAGS "-O0 -Wall ")

add_executable( hexgame ${SOURCE})

include_directories(${OpenGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

target_link_libraries(hexgame ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
if( UNIX)
  install( TARGETS hexgame DESTINATION ~/bin)
endif( UNIX)

target_include_directories( hexgame PUBLIC
  ${PROJECT_SOURCE_DIR}/src
  dep/glm
  dep/cxxopts/include
)


find_package(Doxygen)
set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

add_custom_target( doc_doxygen ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM )
