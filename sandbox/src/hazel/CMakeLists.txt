cmake_minimum_required(VERSION 3.14)

project(hazel LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(HEADER_FILES
    src/hzpch.h
)

add_subdirectory(src/vendor/glfw)
add_subdirectory(src/vendor/glad)
add_subdirectory(src/vendor/imgui)

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
    src/platform/opengl/imgui_impl_opengl_renderer.h src/platform/opengl/imgui_impl_opengl_renderer.cpp
    src/Hazel/layer.h src/Hazel/layer.cpp
    src/Hazel/layerstack.h src/Hazel/layerstack.cpp
    src/Hazel/imgui/imgui_layer.h
    src/Hazel/imgui/imgui_layer.h src/Hazel/imgui/imgui_layer.cpp

)

if(APPLE)
    target_link_libraries(hazel PUBLIC glfw "-framework OpenGL" glad imgui)
else()
    target_link_libraries(hazel PUBLIC glfw glad imgui)
endif()

target_include_directories(hazel PUBLIC
    "${PROJECT_SOURCE_DIR}/src/vendor/spdlog/include"
    "${PROJECT_SOURCE_DIR}/src/vendor/glfw/include"
    "${PROJECT_SOURCE_DIR}/src/vendor/glad/include"
    "${PROJECT_SOURCE_DIR}/src/vendor/imgui"
)

target_precompile_headers(hazel PRIVATE ${HEADER_FILES})
target_compile_definitions(hazel PUBLIC HAZEL_LIBRARY)

