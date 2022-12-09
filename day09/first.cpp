#include <list>
#include <set>
#include "../common/input_utils.h"
#include "../common/string_utils.h"

void makeMove(pair<int, int> &head, pair<int, int> &tail, set<pair<int, int>> &visitedPositions, char command, int numOfMoves);

void moveRight(pair<int, int> &head, pair<int, int> &tail, set<pair<int, int>> &visitedPositions);

void moveLeft(pair<int, int> &head, pair<int, int> &tail, set<pair<int, int>> &visitedPositions);

void moveUp(pair<int, int> &head, pair<int, int> &tail, set<pair<int, int>> &visitedPositions);

void moveDown(pair<int, int> &head, pair<int, int> &tail, set<pair<int, int>> &visitedPositions);

void moveTail(pair<int, int> &head, pair<int, int> &tail);

int distance(pair<int, int> &a, pair<int, int> &b);

int main() {

    vector<string> commands = input_utils::readLines("../data/day09/input.txt");

    set<pair<int, int>> visitedPositions;

    pair<int, int> headPosition(0, 0);
    pair<int, int> tailPosition(0, 0);

    visitedPositions.insert(tailPosition);

    for (string command : commands) {
        vector<string> split = string_utils::split(command);
        makeMove(headPosition, tailPosition, visitedPositions, split.at(0)[0], stoi(split.at(1)));
    }

//    for (auto &pos : visitedPositions) {
//        cout << "(" << pos.first << ", " << pos.second << ")\n";
//    }

    cout << "Positions visited: " << visitedPositions.size();

    return 0;
}

void makeMove(pair<int, int> &head, pair<int, int> &tail, set<pair<int, int>> &visitedPositions, char command, int numOfMoves) {
    for (int i = 0; i < numOfMoves; i++) {
        if (command == 'R') {
            moveRight(head, tail, visitedPositions);
        }
        if (command == 'L') {
            moveLeft(head, tail, visitedPositions);
        }
        if (command == 'U') {
            moveUp(head, tail, visitedPositions);
        }
        if (command == 'D') {
            moveDown(head, tail, visitedPositions);
        }
    }
}

void moveRight(pair<int, int> &head, pair<int, int> &tail, set<pair<int, int>> &visitedPositions) {
    head.first++;
    moveTail(head, tail);
    visitedPositions.insert(tail);
}

void moveLeft(pair<int, int> &head, pair<int, int> &tail, set<pair<int, int>> &visitedPositions) {
    head.first--;
    moveTail(head, tail);
    visitedPositions.insert(tail);
}

void moveUp(pair<int, int> &head, pair<int, int> &tail, set<pair<int, int>> &visitedPositions) {
    head.second++;
    moveTail(head, tail);
    visitedPositions.insert(tail);
}

void moveDown(pair<int, int> &head, pair<int, int> &tail, set<pair<int, int>> &visitedPositions) {
    head.second--;
    moveTail(head, tail);
    visitedPositions.insert(tail);
}

void moveTail(pair<int, int> &head, pair<int, int> &tail) {
    if (distance(head, tail) < 4 ) {
        return;
    }

    list<pair<int,int>> possibleMoves;
    pair<int, int> closestPoint(head.first, head.second);

    possibleMoves.emplace_back(head.first + 1,head.second);
    possibleMoves.emplace_back(head.first - 1,head.second);
    possibleMoves.emplace_back(head.first,head.second + 1);
    possibleMoves.emplace_back(head.first,head.second - 1);

    for (auto &possibleMove : possibleMoves) {
        if (distance(tail, possibleMove) < distance(tail, closestPoint)) {
            closestPoint = possibleMove;
        }
    }

    tail = closestPoint;
}

int distance(pair<int, int> &a, pair<int, int> &b) {
    return abs(a.first - b.first) + abs(a.second- b.second) + max(abs(a.first - b.first), abs(a.second- b.second));
}