cmake_minimum_required(VERSION 3.14)

project(hazel LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(HEADER_FILES
    src/hzpch.h
)

add_subdirectory(src/vendor/glfw)

add_library(hazel SHARED
    src/Hazel/core.h
    src/Hazel/application.h src/Hazel/application.cpp
    src/hazel.h
    src/Hazel/entryPoint.h
    src/Hazel/log.h src/Hazel/log.cpp
    src/Hazel/hazel.h
    src/Hazel/events/event.h
    src/Hazel/events/applicationEvent.h
    src/Hazel/events/keyEvent.h
    src/Hazel/events/mouseEvent.h
    src/hzpch.h
    src/Hazel/window.h
    src/platform/unix/unixwindow.h src/platform/unix/unixwindow.cpp
)

target_link_libraries(hazel PUBLIC glfw "-framework OpenGL")

target_include_directories(hazel PUBLIC
    "${PROJECT_SOURCE_DIR}/src/vendor/spdlog/include"
    "${PROJECT_SOURCE_DIR}/src/vendor/glfw/include"
)

target_precompile_headers(hazel PRIVATE ${HEADER_FILES})
target_compile_definitions(hazel PUBLIC HAZEL_LIBRARY)

