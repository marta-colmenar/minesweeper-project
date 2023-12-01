#include "minesweeper.h"

Minesweeper::Minesweeper(size_t _rows, size_t _cols, size_t _bombs)
    : m_timerStarted(false), m_flagMode(false), m_gameOver(false), m_allCellsRevealedWin(false), m_elapsedTimeInSeconds(0), m_revealedCells(0),
      m_nonBombCells(0), m_rows(_rows), m_cols(_cols), m_bombs(_bombs) {
    // Initialize minefield with empty cells
    m_minefield.resize(_rows, std::vector<CellContent>(m_cols, Empty));
    m_displayMatrix.resize(_rows, std::vector<int>(m_cols, -1));

    initialize();
}

void Minesweeper::render() {
    ImGui::Begin("Minesweeper");

    ImGui::Dummy(ImVec2(0.0f, 10.0f));

    const float buttonSize = 30.0f;
    const float spacing = 1.0f; // Adjust the spacing as needed

    // Flag button
    ImGui::PushStyleColor(ImGuiCol_Button, m_flagMode ? ImVec4(0.5f, 0.7f, 0.9f, 1.0f) : ImVec4(0.3f, 0.2f, 0.9f, 1.0f));
    if (ImGui::Button("Flag Mode")) {
        // Toggle flag mode
        m_flagMode = !m_flagMode;
    }
    ImGui::PopStyleColor();

    ImGui::SameLine(); // Align the next item to the right of the previous one

    // Reset button (use a different color, e.g., light blue)
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.3f, 0.2f, 0.9f, 1.0f)); // Light blue color
    if (ImGui::Button("Reset")) {
        // Add logic here to reset the Minesweeper game
        reset();
    }
    ImGui::PopStyleColor();

    ImGui::SameLine();

    renderGameOverMessage();

    // Add space between buttons and timer
    ImGui::Dummy(ImVec2(0.0f, 10.0f)); // Adjust the height (10.0f) based on your preference

    // Timer display
    ImGui::Text("Time: %02d:%02d", m_elapsedTimeInSeconds / 60, m_elapsedTimeInSeconds % 60);

    // Add space between buttons and grid
    ImGui::Dummy(ImVec2(0.0f, 10.0f)); // Adjust the height (10.0f) based on your preference

    // Check if the timer needs to start
    if (!m_timerStarted && !m_gameOver) {
        m_startTime = std::chrono::high_resolution_clock::now();
        m_timerStarted = true;
    }

    // Update the timer
    if (m_timerStarted && !m_gameOver) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(currentTime - m_startTime);
        m_elapsedTimeInSeconds = static_cast<int>(duration.count());
    }

    ImGui::Columns(static_cast<int>(m_cols), nullptr, false);

    for (size_t r = 0; r < m_rows; ++r) {
        for (size_t c = 0; c < m_cols; ++c) {
            ImGui::PushID(static_cast<int>(r * m_cols + c));

            // Use ImGui::Button to represent each cell
            char label[2] = "";
            ImVec4 buttonColor = ImVec4(0.8f, 0.8f, 0.8f, 1.0f); // Default light grey color

            if (m_gameOver || m_displayMatrix[r][c] != -1) {
                // Revealed cells or flagged cells have a dark grey color
                buttonColor = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
                if (m_gameOver) {
                    label[0] = m_minefield[r][c] == Bomb ? '*' : '0' + static_cast<char>(m_minefield[r][c]);
                } else {
                    label[0] = (m_displayMatrix[r][c] == 'F') ? 'F' : (m_minefield[r][c] == Bomb ? '*' : '0' + static_cast<char>(m_minefield[r][c]));
                }
            }

            ImGui::PushStyleColor(ImGuiCol_Button, buttonColor);

            if (ImGui::Button(label, ImVec2(buttonSize, buttonSize))) {
                if (!m_gameOver) {
                    revealCell(r, c);
                }
            }

            ImGui::PopStyleColor();
            ImGui::PopID();

            ImGui::SetColumnWidth(static_cast<int>(c), buttonSize + spacing);
            ImGui::NextColumn();

        }
    }

    ImGui::Columns(1);

    //renderGameOverMessage();

    ImGui::End();
}

void Minesweeper::revealCell(size_t row, size_t col) {
    if (m_gameOver) {
        return;
    }

    // If in flag mode, place 'F' on the cell
    if (m_flagMode) {
        if (m_displayMatrix[row][col] == -1) {
            // Flag the cell
            m_displayMatrix[row][col] = 'F';
        } else if (m_displayMatrix[row][col] == 'F') {
            // Unflag the cell
            m_displayMatrix[row][col] = -1;
        }
        return;
    }

    // If the cell is already flagged, reveal its content
    if (m_displayMatrix[row][col] == 'F') {
        // Reveal the content of the flagged cell
        m_displayMatrix[row][col] = m_minefield[row][col];

        // Check for bomb and end the game if needed
        if (m_minefield[row][col] == Bomb) {
            gameLost();
        }

        // Increment the count of revealed cells for non-bomb cells only
        if (m_minefield[row][col] != Bomb) {
            m_revealedCells++;

            // Check for a win after revealing a cell
            if (m_revealedCells == m_nonBombCells) {
                gameWon();
            }
        }

        return;
    }

    // If the cell is already revealed or flagged, do nothing
    if (m_displayMatrix[row][col] != -1) {
        return;
    }

    m_displayMatrix[row][col] = m_minefield[row][col];

    if (m_minefield[row][col] == Bomb) {
        gameLost();
    } else if (m_minefield[row][col] == Empty) {
        // If the cell is empty, reveal neighboring cells
        for (int dr = -1; dr <= 1; ++dr) {
            for (int dc = -1; dc <= 1; ++dc) {
                size_t newRow = row + static_cast<size_t>(dr);
                size_t newCol = col + static_cast<size_t>(dc);
                if (newRow >= 0 && newRow < m_rows && newCol >= 0 && newCol < m_cols) {
                    revealCell(newRow, newCol);
                }
            }
        }
    }

    // Increment the count of revealed cells for non-bomb cells only
    if (m_minefield[row][col] != Bomb) {
        m_revealedCells++;

        // Check for a win after revealing a cell
        if (m_revealedCells == m_nonBombCells) {
            gameWon();
        }
    }
}

void Minesweeper::initialize() {
    // Place bombs randomly using <random> library
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(0, m_rows - 1);

    for (size_t i = 0; i < m_bombs; ++i) {
        size_t row, col;
        do {
            row = dist(gen);
            col = dist(gen);
        } while (m_minefield[row][col] == Bomb);
        m_minefield[row][col] = Bomb;
    }

    // Build the hidden matrix with numbers and bombs
    for (std::vector<CellContent>::size_type r = 0; r < m_rows; ++r) {
        for (std::vector<CellContent>::size_type c = 0; c < m_cols; ++c) {
            if (m_minefield[r][c] != Bomb) {
                m_minefield[r][c] = static_cast<CellContent>(countNeighborBombs(r, c));
                m_nonBombCells++; // Increment the count of non-bomb cells
            }
        }
    }
}

void Minesweeper::gameLost() {
    m_gameOver = true;
    m_allCellsRevealedWin = false;  // Set the flag to reveal all cells
}

void Minesweeper::gameWon() {
    m_gameOver = true;
    m_allCellsRevealedWin = true;  // Set the flag to reveal all cells
}

void Minesweeper::renderGameOverMessage() {
    if (m_gameOver) {
        ImGui::SetCursorPosX(ImGui::GetWindowWidth() * 0.5f - 50.0f);
        if (m_allCellsRevealedWin) {
            ImGui::Text("Congratulations! You won!");
        } else {
            ImGui::Text("Game Over! You hit a bomb.");
        }
    }
}

void Minesweeper::reset() {
    // Reset game state variables
    m_gameOver = false;
    m_revealedCells = 0;
    m_allCellsRevealedWin = false;
    // Reset the timer
    m_timerStarted = false;
    m_elapsedTimeInSeconds = 0;

    // Reset displayMatrix to its initial state
    for (size_t r = 0; r < m_rows; ++r) {
        for (size_t c = 0; c < m_cols; ++c) {
            m_displayMatrix[r][c] = -1;  // Assuming -1 represents unrevealed cells
        }
    }
}

size_t Minesweeper::countNeighborBombs(size_t row, size_t col) {
    size_t count = 0;
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            size_t newRow = row + static_cast<size_t>(dr);
            size_t newCol = col + static_cast<size_t>(dc);

            if (newRow >= 0 && newRow < m_rows && newCol >= 0 && newCol < m_cols && m_minefield[newRow][newCol] == Bomb) {
                count++;
            }
        }
    }
    return count;
}
