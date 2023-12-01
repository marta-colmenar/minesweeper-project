#include "difficultySettings.h"

DifficultySettings::DifficultySettings(int _rows, int _cols, int _bombs)
    : m_rows(_rows), m_cols(_cols), m_bombs(_bombs), m_ready(false), m_locked(false) {
}

int DifficultySettings::getBombs() {
    return m_bombs;
}

int DifficultySettings::getRows() {
    return m_rows;
}

int DifficultySettings::getCols() {
    return m_cols;
}

void DifficultySettings::setLockToFalse() {
    m_locked = false;
}

void DifficultySettings::setReadyToFalse() {
    m_ready = false;
}

void DifficultySettings::render() {
    ImGui::Dummy(ImVec2(0.0f, 5.0f));

    ImGui::Text("Adjust the difficulty settings:");

    ImGui::Dummy(ImVec2(0.0f, 10.0f));

    if (!m_locked) {
        ImGui::SliderInt("Rows", &m_rows, 4, m_cols);
        ImGui::SliderInt("Cols", &m_cols, 4, 10);
        ImGui::SliderInt("Bombs", &m_bombs, 1, m_rows * m_cols - 1);
    } else {
        ImGui::Text("Rows: %d", m_rows);
        ImGui::Text("Cols: %d", m_cols);
        ImGui::Text("Bombs: %d", m_bombs);
    }

    ImGui::Dummy(ImVec2(0.0f, 10.0f));

    if (!m_locked && ImGui::Button("OK")) {
        m_ready = true;
        m_locked = true; // Lock difficulty once OK is pressed
    }

}
