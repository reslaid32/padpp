cmake_minimum_required(VERSION 3.15)
project(padpp LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(${INCLUDE_DIR})

file(GLOB LIB_SOURCES ${SRC_DIR}/*.cc)

add_library(padpp SHARED ${LIB_SOURCES})
target_include_directories(padpp PUBLIC ${INCLUDE_DIR})

install(TARGETS padpp
  LIBRARY DESTINATION lib
)

foreach(hdr_dir padpp padpp-c)
  install(DIRECTORY ${INCLUDE_DIR}/${hdr_dir}
          DESTINATION include
          FILES_MATCHING PATTERN "*.h")
endforeach()

configure_file(
  ${CMAKE_SOURCE_DIR}/cmake/uninstall.cmake.in
  ${CMAKE_BINARY_DIR}/uninstall.cmake
  IMMEDIATE @ONLY
)
add_custom_target(uninstall
  COMMAND ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/uninstall.cmake
)
