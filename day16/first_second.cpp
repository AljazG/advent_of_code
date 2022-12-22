#include <list>
#include <unordered_map>
#include <set>
#include <cmath>
#include "../common/input_utils.h"
#include "../common/string_utils.h"
#include "../common/grid_utils.h"

struct Valve {
    int id = 0;
    int flowRate{};
    string name;
    vector<Valve *> toValves;
};

int memo[30][30][20000];

Valve *readInput(vector<string> &input) {
    vector<Valve *> valves;
    unordered_map<string, Valve *> valveMap;

    for (auto line: input) {
        auto *valve = new Valve();
        vector<string> split = string_utils::split(line);
        valve->name = split.at(1);
        vector<string> rateSplit = string_utils::split(split.at(4), "=");
        valve->flowRate = stoi(rateSplit.at(1).substr(0, rateSplit.at(1).length() - 1));
        valves.push_back(valve);
        valveMap.insert({valve->name, valve});
    }
    for (int i = 0; i < valves.size(); i++) {
        auto *valve = valves.at(i);
        valve->id = i;
        vector<string> split = string_utils::split(input.at(i));
        for (int j = 9; j < split.size(); j++) {
            string toValve = split.at(j);
            if (toValve.at(toValve.length() - 1) == ',') {
                toValve = toValve.substr(0, toValve.length() - 1);
            }
            valve->toValves.push_back(valveMap.at(toValve));
        }
    }

    return valves.at(0);
}

int getUniqueId(set<Valve*> &valvesOpened) {
    int sum = 0;
    for (auto valve : valvesOpened) {
        sum += (int) pow(2,valve->id);
    }
    return sum;
}

int mostPressure(Valve *currentValve, int minutes, int pressureBuildup, set<Valve*> valvesOpened, int numOfValves) {
    if (minutes == 0) {
        return 0;
    }
    int uId = getUniqueId(valvesOpened);

    if (memo[minutes - 1][currentValve->id][uId] != -1 && memo[minutes - 1][currentValve->id][uId] >= pressureBuildup) {
        return 0;
    }

    // don't have to move
    if (valvesOpened.size() == numOfValves) {
        return pressureBuildup + mostPressure(currentValve, minutes - 1, pressureBuildup, valvesOpened, numOfValves);
    }

    int max = 0;
    // release valve
    if (valvesOpened.find(currentValve) == valvesOpened.end()) {
        valvesOpened.insert(currentValve);
        max = mostPressure(currentValve, minutes - 1, pressureBuildup + currentValve->flowRate, valvesOpened, numOfValves);
        valvesOpened.erase(currentValve);
    }

    // move To others
    for (auto nextValve : currentValve->toValves) {
        int p = mostPressure(nextValve, minutes - 1, pressureBuildup, valvesOpened, numOfValves);
        if (p > max) {
            max = p;
        }
    }
//    cout << "PLZ " << minutes << "\n";
    cout << "max " << max << "\n";
    memo[minutes - 1][currentValve->id][uId] = pressureBuildup;
    return max + pressureBuildup;
}


int main() {
    vector<string> input = input_utils::readLines("../data/day16/input.txt");
    Valve *start = readInput(input);
    set<Valve*> valvesOpened;
    for (auto & i : memo) {
        for (auto & j : i) {
            for (int & k : j) {
                k = -1;
            }
        }
    }
    int maxPressure = mostPressure(start, 30, 0, valvesOpened, (int)input.size());
    cout << maxPressure;
    return 0;
}