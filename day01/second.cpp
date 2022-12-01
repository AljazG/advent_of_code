#include <iostream>
#include <fstream>
#include <list>
#include "../common/string_utils.h"

using namespace std;

void cropTopThree(list<long>& topThree, list<long>::iterator iter, int counter){
    for (auto it = iter; it != topThree.end(); ++it) {
        if (counter > 1) {
            topThree.erase(it, topThree.end());
            return;
        }
        counter++;
    }
}

void checkIfTopThree(list<long>& topThree, long value){
    if (topThree.empty()) {
        topThree.push_front(value);
        return;
    }
    int counter = 0;
    for (auto it = topThree.begin(); it != topThree.end(); ++it) {
        if (value > *it) {
            topThree.insert(it, value);
            cropTopThree(topThree, it, counter);
            return;
        }
        counter++;
    }
    if (counter < 2) {
        topThree.push_back(value);
    }

}


int main() {

    list<long> topThree;
    long sum = 0;

    ifstream file;

    file.open("../data/day01/input.txt");

    if (file.is_open()){
        string line;
        while (getline(file, line)) {
            if (!string_utils::isBlank(line)) {
                long cal = stol(line);
                sum += cal;
            } else {
                checkIfTopThree(topThree, sum);
                sum = 0;
            }
        }
        checkIfTopThree(topThree, sum);
    }

    long finalSum = 0;
    list<long>::iterator it;
    for (it = topThree.begin(); it != topThree.end(); ++it)
        finalSum += *it;


    cout << "top 3 sum: " << finalSum;
    file.close();

    return 0;
}



