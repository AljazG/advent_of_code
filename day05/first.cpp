#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <sstream>

using namespace std;

void constructStackList(vector<stack<char>> &stackList, vector<string> &drawingLines, int colNum);

void makeMoves(vector<string> &moves, vector<stack<char>> &stackList);

void printStacks(vector<stack<char>> stackList);

int main() {

    ifstream file;

    vector<stack<char>> stackList;
    vector<string> drawingLines;
    vector<string> moves;

    file.open("../data/day05/input.txt");

    bool drawingRead = false;
    int colNum = 0;

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            // read drawing
            if (!drawingRead) {
                // last line of drawing
                if (line[1] == '1') {
                    drawingRead = true;
                    for (int i = line.size() - 1; i >= 0; --i) {
                        if (line[i] != ' ') {
                            colNum = stoi(&line[i]);
                            break;
                        }
                    }
                } else {
                    drawingLines.push_back(line);
                }
            } else if (line[0] != ' ' && !line.empty()) {
                // read moves
                moves.push_back(line);
            }
        }
    }

    constructStackList(stackList, drawingLines, colNum);

    makeMoves(moves, stackList);

    printStacks(stackList);

    for (stack<char> s: stackList) {
        cout << s.top();
    }

    file.close();

    return 0;
}

void constructStackList(vector<stack<char>> &stackList, vector<string> &drawingLines, int colNum) {
    int numOfCharsInLine = (3 * colNum) + (colNum - 1);

    for (int i = 0; i < colNum; i++) {
        stack<char> s;
        stackList.push_back(s);
    }

    for (int i = drawingLines.size() - 1; i >= 0; --i) {
        string line = drawingLines.at(i);
        int j = 1;
        int stackNum = 0;
        while (j < numOfCharsInLine) {
            char x = line[j];
            if (x != ' ' && x != '\0') {
                stackList.at(stackNum).push(x);
            }
            stackNum++;
            j = j + 4;
        }
    }
}

void makeMoves(vector<string> &moves, vector<stack<char>> &stackList) {
    for (string &move: moves) {
        printStacks(stackList);
        stringstream ss(move);
        string ammountStr;
        string fromStr;
        string toStr;

        getline(ss, ammountStr, ' ');
        getline(ss, ammountStr, ' ');

        getline(ss, fromStr, ' ');
        getline(ss, fromStr, ' ');

        getline(ss, toStr, ' ');
        getline(ss, toStr, ' ');

        int ammount = stoi(&ammountStr[0]);
        int fromId = stoi(&fromStr[0]);
        int toId = stoi(&toStr[0]);

        stack<char> *from = &stackList.at(fromId - 1);
        stack<char> *to = &stackList.at(toId - 1);

        for (int i = 0; i < ammount; i++) {
            char x = (*from).top();
            (*from).pop();
            (*to).push(x);
        }

    }
}

void printStacks(vector<stack<char>> stackList) {

    int maxHeight = 0;

    for (auto &stack: stackList) {
        if (stack.size() > maxHeight) {
            maxHeight = stack.size();
        }
    }

    for (int i = maxHeight; i >= 1; --i) {
        for (int j = 0; j < stackList.size(); j++) {
            if (stackList[j].size() >= i) {
                cout << "[" << stackList[j].top() << "]";
                stackList[j].pop();
            } else {
                cout << "   ";
            }
        }
        cout << "\n";
    }

    for (int i = 0; i < stackList.size(); i++) {
        if (i == 0)
            cout << " " << i + 1;
        else
            cout << "  " << i + 1;
    }

    cout << "\n";

    for (int i = 0; i < stackList.size(); i++) {
        cout << "---";
    }

    cout << "\n";

}

