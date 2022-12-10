#include <list>
#include "../common/input_utils.h"

bool isVisible(int i, int j, int **grid, int cols, int rows) {

    //check left
    for (int x = 0; x <= j; x++) {
        if (x == j) {
            return true;
        }
        if (grid[i][x] >= grid[i][j]) {
            break;
        }
    }

    // check right
    for (int x = cols - 1; x >= j; --x) {
        if (x == j) {
            return true;
        }
        if (grid[i][x] >= grid[i][j]) {
            break;
        }
    }

    // check up
    for (int x = 0; x <= i; x++) {
        if (x == i) {
            return true;
        }
        if (grid[x][j] >= grid[i][j]) {
            break;
        }
    }

    // check down
    for (int x = rows - 1; x >= i; --x) {
        if (x == i) {
            return true;
        }
        if (grid[x][j] >= grid[i][j]) {
            break;
        }
    }

    return false;
}

int getScenicScore(int i, int j, int **grid, int cols, int rows) {

    int left = 0;
    int right = 0;
    int up = 0;
    int down = 0;

    //check left
    for (int x = j - 1; x >= 0; x--) {
        left++;
        if (grid[i][x] >= grid[i][j]) {
            break;
        }
    }

    // check right
    for (int x = j + 1; x < cols; x++) {
        right++;
        if (grid[i][x] >= grid[i][j]) {
            break;
        }
    }

    // check up
    for (int x = i - 1; x >= 0; x--) {
        up++;
        if (grid[x][j] >= grid[i][j]) {
            break;
        }
    }

    // check down
    for (int x = i + 1; x < rows; x++) {
        down++;
        if (grid[x][j] >= grid[i][j]) {
            break;
        }
    }

    return right * left * up * down;
}

int main() {

    vector<string> trees = input_utils::readLines("../data/day08/input.txt");

    int cols = (int) trees.at(0).size();
    int rows = (int) trees.size();

    int **grid;

    grid = new int *[rows];
    for (int i = 0; i < rows; i++) {
        grid[i] = new int[cols];
        for (int j = 0; j < cols; j++) {
            grid[i][j] = trees.at(i)[j] - '0';
        }
    }

    int counter = 0;

    for (int i = 1; i < rows - 1; i++) {
        for (int j = 1; j < cols - 1; j++) {
            if (isVisible(i, j, grid, cols, rows)) {
                counter++;
            }
        }
    }

    int scenicScoreMax = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int score = getScenicScore(i, j, grid, cols, rows);
            if (score > scenicScoreMax) {
                scenicScoreMax = score;
            }
        }
    }

    counter = counter + (cols * 2 + (rows - 2) * 2);

    cout << counter << "\n";
    cout << scenicScoreMax << "\n";

    return 0;
}