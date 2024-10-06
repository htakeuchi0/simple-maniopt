cmake_minimum_required(VERSION 3.0)
project(cmake_sample VERSION 0.0.1 LANGUAGES CXX)

add_subdirectory(src)

set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
add_executable(maniopt main.cc)
target_include_directories(maniopt PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

target_link_libraries(maniopt manioptlib blas)

find_program(DOXYGEN doxygen)
if (NOT DOXYGEN)
  message(WARNING "program doxygen not found")
endif()

ADD_CUSTOM_TARGET(docs)
ADD_CUSTOM_COMMAND(
  TARGET docs
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  COMMAND doxygen
  COMMAND mv doxygen/ build/)
