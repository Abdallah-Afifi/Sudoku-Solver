#include "SudokuSolver.h"
#include <iostream>
#include <fstream>
#include <set>

const int N = 9; // Size of the Sudoku grid

SudokuSolver::SudokuSolver() {}

SudokuSolver::~SudokuSolver() {}

void SudokuSolver::printGrid(const std::vector<std::vector<int>>& grid) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            std::cout << grid[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

bool SudokuSolver::isSafe(const std::vector<std::vector<int>>& grid, int row, int col, int num) {
    for (int x = 0; x < N; x++) {
        if (grid[row][x] == num || grid[x][col] == num) {
            return false;
        }
    }

    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

bool SudokuSolver::isValidSudoku(const std::vector<std::vector<int>>& grid) {
    for (int i = 0; i < N; i++) {
        std::set<int> rowSet, colSet;
        for (int j = 0; j < N; j++) {
            if (grid[i][j] != 0 && !rowSet.insert(grid[i][j]).second) {
                return false;
            }
            if (grid[j][i] != 0 && !colSet.insert(grid[j][i]).second) {
                return false;
            }
        }
    }

    for (int startRow = 0; startRow < N; startRow += 3) {
        for (int startCol = 0; startCol < N; startCol += 3) {
            std::set<int> subgridSet;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (grid[startRow + i][startCol + j] != 0 &&
                        !subgridSet.insert(grid[startRow + i][startCol + j]).second) {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

void SudokuSolver::inputGrid(std::vector<std::vector<int>>& grid, const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file '" << fileName << "' for reading." << std::endl;
        exit(1);
    }

    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            file >> grid[row][col];
        }
    }

    file.close();
}

void SudokuSolver::fillHiddenSingles(std::vector<std::vector<int>>& grid) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                std::set<int> possibilities;

                for (int num = 1; num <= 9; num++) {
                    if (isSafe(grid, row, col, num)) {
                        possibilities.insert(num);
                    }
                }

                if (possibilities.size() == 1) {
                    grid[row][col] = *possibilities.begin();
                }
            }
        }
    }
}

bool SudokuSolver::solveSudoku(std::vector<std::vector<int>>& grid) {
    int row, col;
    bool isEmpty = false;
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                isEmpty = true;
                break;
            }
        }
        if (isEmpty) {
            break;
        }
    }

    if (!isEmpty) {
        return true;
    }

    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            if (solveSudoku(grid)) {
                return true;
            }

            grid[row][col] = 0;
        }
    }

    return false;
}
