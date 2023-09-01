cmake_minimum_required(VERSION 3.14)

project(hazel LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(hazel SHARED


  src/Hazel/core.h
  src/Hazel/application.h src/Hazel/application.cpp
  src/hazel.h
  src/Hazel/entryPoint.h
  src/Hazel/log.h src/Hazel/log.cpp
  src/Hazel/hazel.h
)

target_include_directories(hazel PUBLIC
                          "${PROJECT_SOURCE_DIR}/src/vendor/spdlog/include"
                          )

target_compile_definitions(hazel PUBLIC HAZEL_LIBRARY)
