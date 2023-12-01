# Set cmake version
cmake_minimum_required(VERSION 3.10)

# Set Name of project and language
project(Project)

# set build type to Debug/Release
set(CMAKE_BUILD_TYPE "Debug")

# Set the path to your GLFW installation
add_subdirectory(glfw)
add_subdirectory(imgui)

# Set the source files for your project
set(SOURCES
    # Resources files necessary for imgui
    resources/imgui.h
    resources/imconfig.h
    resources/imgui_impl_opengl3.h
    resources/imgui_impl_opengl3.cpp
    resources/imgui_impl_glfw.h
    resources/imgui_impl_glfw.cpp
    resources/imgui_impl_opengl3_loader.h

    # Minesweeper game files
    minesweeper.h
    minesweeper.cpp
    difficultySettings.h
    difficultySettings.cpp
    main.cpp
)

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# link
target_link_libraries(${PROJECT_NAME} PRIVATE glfw imgui)

# Define required c++ standard to C++11
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_11)

# Set compile options, enable warnings
target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>: -Wall>
    $<$<CXX_COMPILER_ID:MSVC>: /W3>
)
