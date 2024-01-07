#ifndef SUDOKUSOLVER_H
#define SUDOKUSOLVER_H

#include <vector>
#include <string>

class SudokuSolver {
public:
    SudokuSolver();
    ~SudokuSolver();

    void printGrid(const std::vector<std::vector<int>>& grid);
    bool solveSudoku(std::vector<std::vector<int>>& grid);
    void fillHiddenSingles(std::vector<std::vector<int>>& grid);
    bool isSafe(const std::vector<std::vector<int>>& grid, int row, int col, int num);
    bool isValidSudoku(const std::vector<std::vector<int>>& grid);
    void inputGrid(std::vector<std::vector<int>>& grid, const std::string& fileName);
};

#endif // SUDOKUSOLVER_H
