#include "SudokuSolver.h"
#include <iostream>

int main() {
    const int N = 9;  // Declare N here

    SudokuSolver solver;
    std::vector<std::vector<int>> grid(N, std::vector<int>(N, 0));

    std::string fileName;
    std::cout << "Enter the file name containing the Sudoku puzzle: ";
    std::cin >> fileName;

    solver.inputGrid(grid, fileName);

    if (!solver.isValidSudoku(grid)) {
        std::cout << "Invalid Sudoku puzzle." << std::endl;
        return 1;
    }

    while (true) {
        solver.fillHiddenSingles(grid);
        if (!solver.solveSudoku(grid) || !solver.isValidSudoku(grid)) {
            std::cout << "No solution exists." << std::endl;
            break;
        }

        bool hiddenSinglesFound = false;
        for (int row = 0; row < N; row++) {
            for (int col = 0; col < N; col++) {
                if (grid[row][col] == 0) {
                    hiddenSinglesFound = true;
                    break;
                }
            }
            if (hiddenSinglesFound) {
                break;
            }
        }
        if (!hiddenSinglesFound) {
            std::cout << "Sudoku solved successfully:" << std::endl;
            solver.printGrid(grid);
            break;
        }
    }

    return 0;
}
