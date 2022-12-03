#include <iostream>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

int getPriority (string& first, string& second, string& third);

int getCharValue(char& x);

int main() {

    ifstream file;

    file.open("../data/day03/input.txt");

    vector<string> list;

    if (file.is_open()){
        string line;
        while (getline(file, line)) {
            list.push_back(line);
        }
    }


    long prioritySum = 0;
    int i = 0;

    while (i < list.size()) {
        string first = list.at(i);
        string second = list.at(i+1);
        string third = list.at(i+2);

        int priority = getPriority(first, second, third);
        prioritySum += priority;
        i = i+3;
    }

    file.close();


    cout << "sum: " << prioritySum;

    return 0;
}

int getPriority(string& first, string& second, string& third) {
    for (char& e1 : first) {
        for (char& e2 : second) {
            if (e1 == e2) {
                for (char& e3 : third) {
                    if (e1 == e3) {
                        return getCharValue(e1);
                    }
                }
            }
        }
    }
    return 0;
}

int getCharValue(char& x) {
    if (x >= 'a' && x <= 'z') {
        return (x - 'a') + 1;
    } else {
        return (x - 'A') + 27;
    }
}


