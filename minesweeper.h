#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <GLFW/glfw3.h>
#include "imgui.h"
#include <vector>
#include <string>
#include <random>
#include <chrono>

class Minesweeper {
public:
    Minesweeper(size_t _rows, size_t _cols, size_t _bombs);
    void render();

private:
    // Avoid Magic Numbers
    enum CellContent { Empty = 0, Bomb = 9 };
    // Variables
    bool m_timerStarted;
    bool m_flagMode;
    bool m_gameOver;
    bool m_allCellsRevealedWin;
    int m_elapsedTimeInSeconds;
    int m_revealedCells; // Number of revealed cells
    int m_nonBombCells;
    size_t m_rows;
    size_t m_cols;
    size_t m_bombs;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime;
    std::vector<std::vector<CellContent> > m_minefield;  // Actual game state (numbers and bombs)
    std::vector<std::vector<int> > m_displayMatrix;  // Displayed state (visible cells)
    // Functions
    void initialize();
    void revealCell(size_t row, size_t col);
    void gameLost();
    void gameWon();
    void renderGameOverMessage();
    void reset();
    size_t countNeighborBombs(size_t row, size_t col);

};

#endif // MINESWEEPER_H
