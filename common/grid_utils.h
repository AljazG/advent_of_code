#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

namespace grid_utils
{

    int getRowsFromInputVector(vector<string> input) {
        return input.size();
    }

    int getColsFromInputVector(vector<string> input) {
        if (!input.empty()) {
            return input.at(0).size();
        }
        return 0;
    }

    int** constructGridIntFromInputVector(vector<string> input) {
        int rows = getRowsFromInputVector(input);
        int cols = getColsFromInputVector(input);
        int** grid = new int*[rows];
        for (int i = 0; i < rows; i++) {
            grid[i] = new int[cols];
            for (int j = 0; j < cols; j++) {
                grid[i][j] = input.at(i)[j] - '0';
            }
        }
        return grid;
    }

    long** constructGridLongFromInputVector(vector<string> input) {
        int rows = getRowsFromInputVector(input);
        int cols = getColsFromInputVector(input);
        long** grid = new long*[rows];
        for (int i = 0; i < rows; i++) {
            grid[i] = new long[cols];
            for (int j = 0; j < cols; j++) {
                grid[i][j] = (long) (input.at(i)[j] - '0');
            }
        }
        return grid;
    }

    char** constructGridCharFromInputVector(vector<string> input) {
        int rows = getRowsFromInputVector(input);
        int cols = getColsFromInputVector(input);
        char** grid = new char*[rows];
        for (int i = 0; i < rows; i++) {
            grid[i] = new char[cols];
            for (int j = 0; j < cols; j++) {
                grid[i][j] = input.at(i)[j];
            }
        }
        return grid;
    }

    void fillGrid(int x, int** grid, int rows, int cols) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                grid[i][j] = x;
            }
        }
    }

    void fillGrid(long x, long** grid, int rows, int cols) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                grid[i][j] = x;
            }
        }
    }

    void fillGrid(char x, char** grid, int rows, int cols) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                grid[i][j] = x;
            }
        }
    }

    long** constructGridLong(int rows, int cols) {
        long** grid = new long*[rows];
        for (int i = 0; i < rows; i++) {
            grid[i] = new long[cols];
        }
        return grid;
    }

    int** constructGridInt(int rows, int cols) {
        int** grid = new int*[rows];
        for (int i = 0; i < rows; i++) {
            grid[i] = new int[cols];
        }
        return grid;
    }

    char** constructGridChar(int rows, int cols) {
        char** grid = new char*[rows];
        for (int i = 0; i < rows; i++) {
            grid[i] = new char[cols];
        }
        return grid;
    }

    long** copyGrid(long** grid, int rows, int cols) {
        long** gridCopy = new long*[rows];
        for (int i = 0; i < rows; i++) {
            gridCopy[i] = new long[cols];
            for (int j = 0; j < cols; j++) {
                gridCopy[i][j] = grid[i][j];
            }
        }
        return grid;
    }

    int** copyGrid(int** grid, int rows, int cols) {
        int** gridCopy = new int*[rows];
        for (int i = 0; i < rows; i++) {
            gridCopy[i] = new int[cols];
            for (int j = 0; j < cols; j++) {
                gridCopy[i][j] = grid[i][j];
            }
        }
        return grid;
    }

    char** copyGrid(char** grid, int rows, int cols) {
        char** gridCopy = new char*[rows];
        for (int i = 0; i < rows; i++) {
            gridCopy[i] = new char[cols];
            for (int j = 0; j < cols; j++) {
                gridCopy[i][j] = grid[i][j];
            }
        }
        return grid;
    }

    void printGrid(char** grid, int rows, int cols) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << grid[i][j];
                if (j == cols - 1)
                    continue;
                cout << " ";
            }
            cout << "\n";
        }
    }

    void printGrid(int** grid, int rows, int cols) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << grid[i][j];
                if (j == cols - 1)
                    continue;
                cout << " ";
            }
            cout << "\n";
        }
    }

    void printGrid(long** grid, int rows, int cols) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << grid[i][j];
                if (j == cols - 1)
                    continue;
                cout << " ";
            }
            cout << "\n";
        }
    }
}
