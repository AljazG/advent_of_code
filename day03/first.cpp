#include <iostream>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

int getPriority(string &first, string &second);

int getCharValue(char &x);

int main() {

    ifstream file;

    file.open("../data/day03/input.txt");

    vector<string> list;

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            list.push_back(line);
        }
    }


    long prioritySum = 0;

    for (const string &content: list) {
        long length = content.size();
        string first = content.substr(0, (length / 2));
        string second = content.substr((length / 2), length - (length / 2));
        int priority = getPriority(first, second);
        prioritySum += priority;
    }

    file.close();


    cout << "sum: " << prioritySum;

    return 0;
}

int getPriority(string &first, string &second) {
    for (char &e1: first) {
        for (char &e2: second) {
            if (e1 == e2) {
                return getCharValue(e1);
            }
        }
    }
    return 0;
}

int getCharValue(char &x) {
    if (x >= 'a' && x <= 'z') {
        return (x - 'a') + 1;
    } else {
        return (x - 'A') + 27;
    }
}


