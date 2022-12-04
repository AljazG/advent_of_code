#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

pair<int, int> getRange(string &string);

bool contains(pair<int,int> &p1, pair<int,int> &p2);

int main() {
    ifstream file;

    file.open("../data/day04/input.txt");

    vector<string> list;

    int counter = 0;

    if (file.is_open()){
        string line;
        while (getline(file, line)) {

            stringstream ss(line);

            string first;
            string second;

            getline(ss, first, ',');
            getline(ss, second, ',');

            pair<int, int> firstPair = getRange(first);
            pair<int, int> secondPair = getRange(second);
            cout <<  firstPair.first << " " << firstPair.second;
            cout <<  " and " <<  secondPair.first << " " << secondPair.second << "\n";

            if (contains(firstPair, secondPair)) {
                counter ++;
                cout << "BINGO! \n";
            }
        }
        cout << "counter: " << counter << "\n";
    }
    return 0;
}

pair<int, int> getRange(string &str) {
    stringstream ss(str);
    string first;
    string second;
    getline(ss, first, '-');
    getline(ss, second, '-');
    pair<int, int> out(stol(&first[0]),stol(&second[0]));
    return out;
}

bool contains(pair<int,int> &p1, pair<int,int> &p2) {
    if (p1.first >= p2.first && p1.second <= p2.second) {
        return true;
    }
    if (p2.first >= p1.first && p2.second <= p1.second) {
        return true;
    }
    return false;
}


