#include <iostream>
#include <fstream>
#include "../common/string_utils.h"

using namespace std;

int main() {

    long max = 0;
    int maxI = 0;
    long sum = 0;
    int i = 0;

    ifstream file;

    file.open("../data/day01/input.txt");

    if (file.is_open()){
        string line;
        while (getline(file, line)) {
            if (!string_utils::isBlank(line)) {
                long cal = stol(line);
                sum += cal;
            } else {
                if (sum > max) {
                    max = sum;
                    maxI = i;
                }
                sum = 0;
                i++;
            }
        }
        if (sum > max) {
            max = sum;
            maxI = i;
        }
    }

    file.close();

    cout << "max sum: " << max << " elf number: " << (maxI + 1);
    return 0;
}
