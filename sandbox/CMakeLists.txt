cmake_minimum_required(VERSION 3.5)

project(sandbox LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src/hazel)

add_executable(sandbox src/sandboxApp.cpp)

target_link_libraries(sandbox PUBLIC hazel)

target_include_directories(sandbox PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/src/hazel"
                          )

include(GNUInstallDirs)
install(TARGETS sandbox
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
