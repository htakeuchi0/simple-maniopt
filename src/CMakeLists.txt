add_library(manioptlib SHARED
  matrix.cc
  retruction.cc
  vector.cc)

target_include_directories(manioptlib PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

install(TARGETS manioptlib
  EXPORT manioptlib-config
  LIBRARY DESTINATION lib)

install(EXPORT manioptlib-config
  NAMESPACE manioptlib::
  DESTINATION lib/cmake/manioptlib)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/manioptlib-config-version.cmake
    COMPATIBILITY SameMajorVersion)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/manioptlib-config-version.cmake
    DESTINATION lib/cmake/manioptlib)

add_library(manioptlib::manioptlib ALIAS manioptlib)
