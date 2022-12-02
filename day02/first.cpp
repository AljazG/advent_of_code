#include <iostream>
#include <fstream>
#include <map>

using namespace std;

const int ROCK = 1;
const int PAPER = 2;
const int SCISSORS = 3;

map<char, int> rpsMap = {
    {'X', ROCK},
    {'Y', PAPER},
    {'Z', SCISSORS},
    {'A', ROCK},
    {'B', PAPER},
    {'C', SCISSORS},
};

int mapToRps(char character) {
  return rpsMap[character];
}

int calculateScore(int elf, int me) {
    // draw
    if (elf == me) {
       return 3 + me;
    }
    // win
    if (elf == ROCK && me == PAPER) {
        return me + 6;
    } else if (elf == PAPER && me == SCISSORS) {
        return me + 6;
    } else if (elf == SCISSORS && me == ROCK) {
        return me + 6;
    }
    // loss
    return me;
}

int main() {

    ifstream file;

    file.open("../data/day02/input.txt");

    long sum = 0;

    if (file.is_open()){
        string line;
        while (getline(file, line)) {
            int elf = mapToRps(line[0]);
            int me = mapToRps(line[2]);
            int score = calculateScore(elf, me);
            sum += score;
        }
    }

    file.close();

    cout << "sum: " << sum;

    return 0;
}
