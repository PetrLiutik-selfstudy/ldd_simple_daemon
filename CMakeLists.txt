cmake_minimum_required(VERSION 3.0)cmake_minimum_required(VERSION 3.1)

project(ldd_simple_deamon LANGUAGES CXX)

include_directories(
  ${PROJECT_SOURCE_DIR}/inc
)

target_sources(
  ${PROJECT_SOURCE_DIR}/src/main.cpp
)
