cmake_minimum_required(VERSION 3.14)
project(GeometricPredicates)

### Header-only lib
add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} INTERFACE "${PROJECT_SOURCE_DIR}/include")

option (GP_BUILD_TESTS "Build unit tests." ON)
option (GP_BUILD_DEMO "Build demo." ON)

### Tests
if (${GP_BUILD_TESTS})
  enable_testing ()
  add_subdirectory ("${${PROJECT_NAME}_SOURCE_DIR}/Testing")
endif ()

### Demo
if ($GP_BUILD_DEMO)
  add_executable(demo)
  target_sources(demo PRIVATE "${PROJECT_SOURCE_DIR}/demo.cpp")
  target_link_libraries(demo PRIVATE ${PROJECT_NAME})
  target_compile_features(demo PRIVATE cxx_std_17)
  if (MSVC)
    target_compile_options(demo PRIVATE "/Zc:__cplusplus")
  endif ()
endif ()