#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>
#include "minesweeper.h"
#include "difficultySettings.h"

// Function to render instructions window
static void renderInstructionsWindow() {
    ImGui::Begin("Instructions");
    ImGui::Text("Welcome to Minesweeper!");
    ImGui::Text("Instructions:");
    ImGui::BulletText("Left-click to reveal a cell.");
    ImGui::BulletText("Flag-mode to flag or unflag a cell as a potential mine.");
    ImGui::BulletText("Avoid clicking on a mine");
    ImGui::End();
}

// Function to handle ImGui setup
static void initializeImGui(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

// Function to handle ImGui cleanup
static void cleanupImGui() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 630, "Minesweeper", nullptr, nullptr);

    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    initializeImGui(window);

    int rows = 4;
    int cols = 4;
    int bombs = 6;

    DifficultySettings difficultySettings(rows, cols, bombs);
    std::unique_ptr<Minesweeper> minesweeper = nullptr;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        difficultySettings.render();

        if (difficultySettings.isReady() && minesweeper == nullptr) {
            rows = difficultySettings.getRows();
            cols = difficultySettings.getCols();
            bombs = difficultySettings.getBombs();

            minesweeper = std::make_unique<Minesweeper>(rows, cols, bombs);
        }

        if (minesweeper != nullptr) {
            minesweeper->render();
        }

        renderInstructionsWindow();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    cleanupImGui();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}



