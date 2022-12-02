#include <iostream>
#include <fstream>
#include <map>
#include "../common/string_utils.h"


const int ROCK = 1;
const int PAPER = 2;
const int SCISSORS = 3;

const int LOSE = 4;
const int DRAW = 5;
const int WIN = 6;


map<char, int> rpsMap = {
    {'A', ROCK},
    {'B', PAPER},
    {'C', SCISSORS},
    {'X', LOSE},
    {'Y', DRAW},
    {'Z', WIN},
};


using namespace std;

int mapToRps(char character) {
  return rpsMap[character];
}

int calculateScore(int elf, int outcome) {
    // draw
    if (outcome == DRAW) {
       return 3 + elf;
    }

    if (outcome == WIN) {
        if (elf == ROCK) {
            return PAPER + 6;
        } else if (elf == PAPER) {
            return SCISSORS + 6;
        } else {
            return ROCK + 6;
        }
    }

    if (outcome == LOSE) {
        if (elf == ROCK) {
            return SCISSORS;
        } else if (elf == PAPER) {
            return ROCK;
        } else {
            return PAPER;
        }
    }

    // shouldn't come here
    return 0;
}

int main() {

    ifstream file;

    file.open("../data/day02/input.txt");

    long sum = 0;

    if (file.is_open()){
        string line;
        while (getline(file, line)) {
            int elf = mapToRps(line[0]);
            int outcome = mapToRps(line[2]);
            int score = calculateScore(elf, outcome);
            sum += score;
        }
    }

    file.close();

    cout << "sum: " << sum;

    return 0;
}
