#ifndef DIFFICULTYSETTINGS_H
#define DIFFICULTYSETTINGS_H

#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class DifficultySettings {
public:
    DifficultySettings(int rows, int cols, int bombs);

    void render();

    bool isReady() const { return m_ready; }
    bool isLocked() const { return m_locked; }
    int getRows();
    int getCols();
    int getBombs();
    void setLockToFalse();
    void setReadyToFalse();

private:
    int m_rows;
    int m_cols;
    int m_bombs;
    bool m_ready;
    bool m_locked; // Added variable to track if difficulty is locked
};

#endif // DIFFICULTYSETTINGS_H

