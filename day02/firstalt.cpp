#include <iostream>
#include <fstream>
#include <map>

using namespace std;

map<string, int> rpsMap = {
        {"AX", 4},
        {"AY", 8},
        {"AZ", 3},
        {"BX", 1},
        {"BY", 5},
        {"BZ", 9},
        {"CX", 7},
        {"CY", 2},
        {"CZ", 6},
};

int main() {

    ifstream file;

    file.open("../data/day02/input.txt");

    long sum = 0;

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            int score = rpsMap[string(1, line[0]) + line[2]];
            sum += score;
        }
    }

    file.close();

    cout << "sum: " << sum;

    return 0;
}
