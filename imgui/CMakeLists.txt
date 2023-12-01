cmake_minimum_required(VERSION 3.0)

# Set name, version and language of project
project(imgui VERSION 1.0.0 LANGUAGES CXX)

set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui-master)
add_library(${PROJECT_NAME} STATIC)

target_sources( ${PROJECT_NAME}
    PRIVATE
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui.cpp

    PRIVATE
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)


target_include_directories( ${PROJECT_NAME}
    PUBLIC ${IMGUI_DIR}
    PUBLIC ${IMGUI_DIR}/backends
)

find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC ${OPENGL_LIBRARIES})

# Set compile options, enable warnings
target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>: -Wall>
    $<$<CXX_COMPILER_ID:MSVC>: /W3>
)
