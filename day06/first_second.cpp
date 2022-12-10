#include <list>
#include "../common/input_utils.h"

using namespace std;

bool containsDuplicates(list<char> &charList) {
    for (auto it = charList.begin(); it != charList.end(); ++it) {
        for (auto it2 = it; it2 != charList.end(); ++it2) {
            if (*it == *it2 && it != it2) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    string inputString = input_utils::readLinesConcat("../data/day06/input.txt");
    list<char> previous;

    // first: 4, second: 14
    int previousSize = 14;

    int index = -1;

    for (int i = 0; i < inputString.size(); i++) {
        if (previous.size() < previousSize) {
            previous.push_back(inputString[i]);
        } else if (containsDuplicates(previous)) {
            previous.erase(previous.begin());
            previous.push_back(inputString[i]);
        } else {
            index = i;
            break;
        }
    }

    if (index == -1 && !containsDuplicates(previous)) {
        index = (int) inputString.size() - 1;
    }

    for (auto &e: previous) {
        cout << e;
    }

    cout << "\n";
    cout << index;

    return 0;
}

