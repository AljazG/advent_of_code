#include <list>
#include <set>
#include "../common/input_utils.h"
#include "../common/string_utils.h"
#include "../common/grid_utils.h"


void getStartAndEndPos(pair<int, int> &startPos, pair<int, int> &endPos, char **grid, int rows, int cols) {
    bool foundStart = false;
    bool foundEnd = false;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 'S') {
                startPos = pair(i, j);
                foundStart = true;
            }
            if (grid[i][j] == 'E') {
                endPos = pair(i, j);
                foundEnd = true;
            }
            if (foundStart && foundEnd) {
                return;
            }
        }
    }
}

char checkStartEnd(char &x) {
    if (x == 'S') {
        return 'a';
    }
    if (x == 'E') {
        return 'z';
    }
    return x;
}

bool canTravel(pair<int, int> &fromPair, pair<int, int> &toPair, char **grid, int rows, int cols) {
    if (toPair.first < 0 || toPair.first >= rows || toPair.second < 0 || toPair.second >= cols) {
        return false;
    }
    char from = checkStartEnd(grid[fromPair.first][fromPair.second]);
    char to = checkStartEnd(grid[toPair.first][toPair.second]);
    return (to - 'a') <= (from - 'a') + 1;
}

pair<int, int> popMinDistPair(set<pair<int, int>> &nodesForSelection, int **grid) {
    int min = INT_MAX;
    pair<int, int> minNode;
    for (auto node: nodesForSelection) {
        if (grid[node.first][node.second] < min) {
            minNode = node;
            min = grid[node.first][node.second];
        }
    }
    nodesForSelection.erase(minNode);
    return minNode;
}

int getMinDistance(pair<int, int> startPos, pair<int, int> endPos, char **grid, int rows, int cols) {
    int **distancesGrid = grid_utils::constructGridInt(rows, cols);
    grid_utils::fillGrid(INT_MAX, distancesGrid, rows, cols);

    distancesGrid[startPos.first][startPos.second] = 0;

    set<pair<int, int>> finishedNodes;
    set<pair<int, int>> nodesForSelection;
    nodesForSelection.insert(startPos);

    while (finishedNodes.count(endPos) == 0 && !nodesForSelection.empty()) {
        pair<int, int> current = popMinDistPair(nodesForSelection, distancesGrid);

        pair<int, int> to(current.first, current.second + 1);
        if (finishedNodes.count(to) == 0 && canTravel(current, to, grid, rows, cols)) {
            if (distancesGrid[current.first][current.second] + 1 < distancesGrid[to.first][to.second]) {
                distancesGrid[to.first][to.second] = distancesGrid[current.first][current.second] + 1;
                nodesForSelection.insert(to);
            }
        }

        to.first = current.first;
        to.second = current.second - 1;
        if (finishedNodes.count(to) == 0 && canTravel(current, to, grid, rows, cols)) {
            if (distancesGrid[current.first][current.second] + 1 < distancesGrid[to.first][to.second]) {
                distancesGrid[to.first][to.second] = distancesGrid[current.first][current.second] + 1;
                nodesForSelection.insert(to);
            }
        }

        to.first = current.first + 1;
        to.second = current.second;
        if (finishedNodes.count(to) == 0 && canTravel(current, to, grid, rows, cols)) {
            if (distancesGrid[current.first][current.second] + 1 < distancesGrid[to.first][to.second]) {
                distancesGrid[to.first][to.second] = distancesGrid[current.first][current.second] + 1;
                nodesForSelection.insert(to);
            }
        }

        to.first = current.first - 1;
        to.second = current.second;
        if (finishedNodes.count(to) == 0 && canTravel(current, to, grid, rows, cols)) {
            if (distancesGrid[current.first][current.second] + 1 < distancesGrid[to.first][to.second]) {
                distancesGrid[to.first][to.second] = distancesGrid[current.first][current.second] + 1;
                nodesForSelection.insert(to);
            }
        }

        finishedNodes.insert(current);

    }

    if (nodesForSelection.empty() && finishedNodes.size() < (rows * cols)) {
        return INT_MAX;
    }

    return distancesGrid[endPos.first][endPos.second];
}


int main() {

    vector<string> input = input_utils::readLines("../data/day12/input.txt");

    int rows = grid_utils::getRowsFromInputVector(input);
    int cols = grid_utils::getColsFromInputVector(input);

    char **grid = grid_utils::constructGridCharFromInputVector(input);

    pair<int, int> startPos;
    pair<int, int> endPos;

    getStartAndEndPos(startPos, endPos, grid, rows, cols);

    // first
    cout << getMinDistance(startPos, endPos, grid, rows, cols) << "\n";

    list<pair<int, int>> startPosList;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 'a' || grid[i][j] == 'S') {
                startPosList.emplace_back(i, j);
            }
        }
    }

    int minDist = INT_MAX;

    for (auto pos: startPosList) {
        int dist = getMinDistance(pos, endPos, grid, rows, cols);
        if (dist < minDist) {
            minDist = dist;
        }
    }

    cout << minDist << "\n";

    return 0;
}