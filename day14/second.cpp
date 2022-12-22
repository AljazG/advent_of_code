#include <list>
#include "../common/input_utils.h"
#include "../common/string_utils.h"
#include "../common/grid_utils.h"

void parseLines(vector<string> &lines, vector<list<pair<int, int>>> &paths) {
    for (int i = 0; i < paths.size(); i++) {
        vector<string> path = string_utils::split(lines.at(i), " -> ");
        list<pair<int, int>> l;
        for (auto &coord: path) {
            vector<string> coords = string_utils::split(coord, ",");
            pair<int, int> p(stoi(coords.at(0)), stoi(coords.at(1)));
            l.push_back(p);
        }
        paths.at(i) = l;
    }
}

char **constructGrid(vector<list<pair<int, int>>> &paths, int &startIndex, int &rows, int &cols, int &offset) {
    int maxRow = 0;
    int minCol = INT_MAX;

    for (auto &list: paths) {
        for (auto pair: list) {
            if (pair.second > maxRow) {
                maxRow = pair.second;
            }
            if (pair.first < minCol) {
                minCol = pair.first;
            }
        }
    }

    rows = maxRow + 1 + 2;
    cols = (rows - 2) * 2 + 5;
    offset = (((rows - 2) * 2 + 4) / 2) - (500 - minCol);
    startIndex = minCol;

    return grid_utils::constructGridChar(rows, cols);
}

void placeRockLine(pair<int, int> &from, pair<int, int> &to, char **grid, int &startIndex, int &offset) {
    int direction;
    if (from.second == to.second) {
        if (to.first - from.first > 0) {
            direction = 1;
        } else {
            direction = -1;
        }
        for (int i = from.first - startIndex; i != (to.first - startIndex + direction); i += direction) {
            grid[from.second][i + offset] = '#';
        }
    }

    if (from.first == to.first) {
        if (to.second - from.second > 0) {
            direction = 1;
        } else {
            direction = -1;
        }
        for (int i = from.second; i != to.second + direction; i += direction) {
            grid[i][from.first - startIndex + offset] = '#';
        }
    }
}

void placeRocks(char **grid, vector<list<pair<int, int>>> &paths, int &startIndex, int &offset, int &rows, int &cols) {
    for (auto &list: paths) {
        for (auto it = list.begin(); it != prev(list.end(), 1); ++it) {
            pair<int, int> from = *it;
            pair<int, int> to = *next(it, 1);
            placeRockLine(from, to, grid, startIndex, offset);
        }
    }

    for (int i = 0; i < cols; i++) {
        grid[rows-1][i] = '#';
    }

}

int posRanking(char **grid, int i, int j, int &rows, int &cols) {
    if (i < 0 || i >= rows || j < 0 || j >= cols) {
        return 1;
    }
    if (grid[i][j] == '.') {
        return 1;
    }
    if (grid[i][j] == '#' || grid[i][j] == 'o') {
        return 0;
    }
}

bool moveSandBlock(char **grid, int &startIndex, int &offset, int &rows, int &cols) {
    int i = 0;
    int j = 500 - startIndex + offset;
    while (true) {
        if (posRanking(grid, (i + 1), j, rows, cols) == 1) {
            i++;
        } else if (posRanking(grid, (i + 1), (j - 1), rows, cols) == 1) {
            i++;
            j--;
        } else if (posRanking(grid, (i + 1), (j + 1), rows, cols) == 1) {
            i++;
            j++;
        } else {
            grid[i][j] = 'o';
            if (i == 0 && j - offset + startIndex == 500) {
               return false;
            }
            return true;
        }
        if (i < 0 || i >= rows || j < 0 || j >= cols) {
            return false;
        }
    }
}

int main() {

    vector<string> lines = input_utils::readLines("../data/day14/input.txt");
    vector<list<pair<int, int>>> paths(lines.size());
    parseLines(lines, paths);
    int rows;
    int cols;
    int startIndex;
    int offset = 0;
    char **grid = constructGrid(paths, startIndex, rows, cols, offset);
    grid_utils::fillGrid('.', grid, rows, cols);
    placeRocks(grid, paths, startIndex, offset, rows, cols);

    int i = 0;

    while (moveSandBlock(grid, startIndex, offset, rows, cols)) {
        ++i;
    }

    grid_utils::printGrid(grid, rows, cols);

    cout << i + 1 << "\n";

    return 0;
}