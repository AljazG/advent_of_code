#include <list>
#include <unordered_map>
#include "../common/input_utils.h"
#include "../common/string_utils.h"
#include "../common/grid_utils.h"

struct Sensor {
    long x = 0;
    long y = 0;
};

struct Beacon {
    long x = 0;
    long y = 0;
};

void insertCoordinateIntoMap(unordered_map<long, bool> &map, long x) {
    map.emplace(x, true);
}

void readInput(vector<string> &lines, list<pair<Sensor, Beacon>> &sensorBeaconList,
               list<pair<long, long>> &beacons,
               list<pair<long, long>> &sensors) {
    for (auto &line: lines) {
        vector<string> split = string_utils::split(line);
        string sensorX = split[2].substr(2, split[2].length() - 3);
        string sensorY = split[3].substr(2, split[3].length() - 3);
        string beaconX = split[8].substr(2, split[8].length() - 3);
        string beaconY = split[9].substr(2, split[9].length() - 2);
        Sensor sensor;
        sensor.x = stol(sensorX);
        sensor.y = stol(sensorY);
        Beacon beacon;
        beacon.x = stol(beaconX);
        beacon.y = stol(beaconY);
        sensorBeaconList.emplace_back(sensor, beacon);
        beacons.emplace_back(beacon.x, beacon.y);
        sensors.emplace_back(sensor.x, sensor.y);
    }
}

long manhattan(long x1, long y1, long x2, long y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

bool compFun(pair<long, long> &range1, pair<long, long> &range2) {
    return range1.first < range2.first;
}

long rangesCoverWholeRow(list<pair<long, long>> &rangesCovered, const long &max) {
    rangesCovered.sort(compFun);

    if (rangesCovered.empty()) {
        return false;
    }

    if (rangesCovered.begin()->first > 0) {
        return false;
    }

    for (auto it = rangesCovered.begin(); it != prev(rangesCovered.end(), 1); ++it) {
        if (it->second < next(it, 1)->first - 1) {
            return false;
        }
        next(it, 1)->second = std::max(next(it, 1)->second, it->second);
    }

    if (prev(rangesCovered.end(), 1)->second < max) {
        return false;
    }

    return true;
}


int main() {

    const long max = 4000000;

    vector<string> lines = input_utils::readLines("../data/day15/input.txt");
    list<pair<Sensor, Beacon>> sensorBeaconList;
    list<pair<long, long>> beacons;
    list<pair<long, long>> sensors;


    readInput(lines, sensorBeaconList, beacons, sensors);




    for (long j = 0; j <= max; j++) {

        list<pair<long, long>> rangesCovered;
        for (auto &sensorBeaconPair: sensorBeaconList) {
            Sensor sensor = sensorBeaconPair.first;
            Beacon beacon = sensorBeaconPair.second;
            long man = manhattan(sensor.x, sensor.y, beacon.x, beacon.y);

            long x = sensor.x;
            long y = j;

            long distToSensor = abs(y - sensor.y);

            if (distToSensor <= man) {
                rangesCovered.emplace_back(x - (man - distToSensor), x + (man - distToSensor));
            }

        }
        if (!rangesCoverWholeRow(rangesCovered, max)) {
            cout << " line: " << j << "\n";
            rangesCovered.sort(compFun);
            for (auto it = rangesCovered.begin(); it != prev(rangesCovered.end(), 1); ++it) {
                if (it->second < next(it, 1)->first - 1) {
                    long x = next(it, 1)->first - 1;
                    cout << "x= " << x << "\n";
                    cout << "answer: " << 4000000 * x + j;
                    return 0;
                }
            }

        }
    }

    return 0;
}