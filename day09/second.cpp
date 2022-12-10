#include <list>
#include <set>
#include "../common/input_utils.h"
#include "../common/string_utils.h"

struct Node {
    pair<int, int> coordinates;
    Node *next{};
    bool tail{};
    bool head{};
};

void makeMove(list<Node *> &snake, set<pair<int, int>> &visitedPositions, char command, int numOfMoves);

void moveRight(Node *next, Node *prev);

void moveLeft(Node *next, Node *prev);

void moveUp(Node *next, Node *prev);

void moveDown(Node *next, Node *prev);

void movePrevNode(Node *next, Node *prev);

int distance(pair<int, int> &a, pair<int, int> &b);

int main() {

    vector<string> commands = input_utils::readLines("../data/day09/input.txt");

    set<pair<int, int>> visitedTailPositions;
    list<Node *> snake;

    int numOfParts = 10;


    visitedTailPositions.insert(pair(0, 0));

    for (int i = 0; i < numOfParts; i++) {
        Node *node = new Node();
        node->coordinates = pair(0, 0);
        node->tail = false;
        node->head = false;
        snake.push_back(node);
    }

    snake.front()->head = true;
    snake.back()->tail = true;

    for (auto it = snake.begin(); it != snake.end(); ++it) {
        if ((*it)->tail) {
            break;
        }
        auto nextIt = next(it, 1);
        (*nextIt)->next = *it;
    }

    for (string command: commands) {
        vector<string> split = string_utils::split(command);
        makeMove(snake, visitedTailPositions, split.at(0)[0], stoi(split.at(1)));
    }

//    for (auto &pos : visitedTailPositions) {
//        cout << "(" << pos.first << ", " << pos.second << ")\n";
//    }

    cout << "Positions visited: " << visitedTailPositions.size();

    return 0;
}

void makeMove(list<Node *> &snake, set<pair<int, int>> &visitedPositions, char command, int numOfMoves) {
    for (int i = 0; i < numOfMoves; i++) {
        for (auto &it: snake) {
            if (it->head) {
                continue;
            }

            if (command == 'R') {
                moveRight(it->next, it);
            }
            if (command == 'L') {
                moveLeft(it->next, it);
            }
            if (command == 'U') {
                moveUp(it->next, it);
            }
            if (command == 'D') {
                moveDown(it->next, it);
            }

            if (it->tail) {
                visitedPositions.insert(it->coordinates);
            }
        }
    }


}

void moveRight(Node *next, Node *prev) {
    if (next->head) {
        next->coordinates.first++;
    }
    movePrevNode(next, prev);
}

void moveLeft(Node *next, Node *prev) {
    if (next->head) {
        next->coordinates.first--;
    }
    movePrevNode(next, prev);
}

void moveUp(Node *next, Node *prev) {
    if (next->head) {
        next->coordinates.second++;
    }
    movePrevNode(next, prev);
}

void moveDown(Node *next, Node *prev) {
    if (next->head) {
        next->coordinates.second--;
    }
    movePrevNode(next, prev);
}

void movePrevNode(Node *next, Node *prev) {
    pair<int, int> nextCoor = next->coordinates;
    pair<int, int> prevCoor = prev->coordinates;

    if (distance(nextCoor, prevCoor) < 4) {
        return;
    }

    list<pair<int, int>> possibleMoves;
    pair<int, int> closestPoint(nextCoor.first, nextCoor.second);

    if (distance(nextCoor, prevCoor) == 6) {
        possibleMoves.emplace_back(nextCoor.first + 1, nextCoor.second + 1);
        possibleMoves.emplace_back(nextCoor.first + 1, nextCoor.second - 1);
        possibleMoves.emplace_back(nextCoor.first - 1, nextCoor.second + 1);
        possibleMoves.emplace_back(nextCoor.first - 1, nextCoor.second - 1);
    } else {
        possibleMoves.emplace_back(nextCoor.first + 1, nextCoor.second);
        possibleMoves.emplace_back(nextCoor.first - 1, nextCoor.second);
        possibleMoves.emplace_back(nextCoor.first, nextCoor.second + 1);
        possibleMoves.emplace_back(nextCoor.first, nextCoor.second - 1);
    }

    for (auto &possibleMove: possibleMoves) {
        if (distance(prevCoor, possibleMove) < distance(prevCoor, closestPoint)) {
            closestPoint = possibleMove;
        }
    }

    prev->coordinates = closestPoint;
}

int distance(pair<int, int> &a, pair<int, int> &b) {
    return abs(a.first - b.first) + abs(a.second - b.second) + max(abs(a.first - b.first), abs(a.second - b.second));
}