# Minesweeper C++ Project
## Overview
This Minesweeper project is developed as the final project for a C++ course. It provides a simple Minesweeper game implemented in C++ using the GLFW library for GUI and ImGui for user interface elements.

<img width="397" alt="minesweeper_game" src="https://github.com/marta-colmenar/minesweeper-project/assets/73017799/66d9a560-6a99-4c9e-99c2-c3ff20d7dca5">

## Features
- Classic Minesweeper gameplay.
- Adjustable difficulty settings (rows, columns, bombs).
- User-friendly GUI with ImGui.
- Timer to track gameplay duration.
- Flag mode for marking potential bomb locations.
- Game over screen with victory or defeat messages.

## How to Play
- Left-click to reveal a cell.
- Use flag mode to flag or unflag a cell as a potential mine.
- Avoid clicking on a mine.
- The game is won when all non-bomb cells are revealed.
- The game is lost if a mine is revealed.

## Compiling and Running
To compile and run the Minesweeper game, ensure you have the following dependencies installed (the libraries are included in the repository):

- CMake (minimum version 3.10)
- GLFW 3.3.8
- ImGui

## Project Structure
- minesweeper.cpp: Main implementation of the Minesweeper game, logic of the game.
- minesweeper.h: Header file containing Minesweeper class declaration.
- difficultySettings.cpp: Implementation of difficulty settings to choose number of bombs, rows and columns.
- difficultySettings.h: Header file for difficulty settings.
- main.cpp: Main entry point of the program.
- resources/: Directory containing ImGui resource files.
