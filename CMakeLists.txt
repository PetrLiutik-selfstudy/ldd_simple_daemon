cmake_minimum_required(VERSION 3.2)

project(ldd_simple_deamon VERSION 1.0.0)

add_executable(${PROJECT_NAME}
  ${PROJECT_SOURCE_DIR}/src/main.cpp
  ${PROJECT_SOURCE_DIR}/src/daemon.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
  ${PROJECT_SOURCE_DIR}/inc
  ${PROJECT_SOURCE_DIR}/src
)

set_target_properties(${PROJECT_NAME} PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)