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


int main() {

    vector<string> lines = input_utils::readLines("../data/day15/input.txt");
    list<pair<Sensor, Beacon>> sensorBeaconList;
    list<pair<long, long>> beacons;
    list<pair<long, long>> sensors;


    readInput(lines, sensorBeaconList, beacons, sensors);

    unordered_map<long, bool> pointsInLine;

    unordered_map<long, bool> objectsInLine;

    long lineY = 2000000;

    long minX = LONG_MAX;
    long maxX = 0;

    for (auto &beacon: beacons) {
        if (beacon.second == lineY) {
            insertCoordinateIntoMap(objectsInLine, beacon.first);
        }
        if (beacon.first > maxX) {
            maxX = beacon.first;
        }
        if (beacon.first < minX) {
            minX = beacon.first;
        }
    }

    for (auto &pair: sensorBeaconList) {
        long man = manhattan(pair.first.x, pair.first.y, pair.second.x, pair.second.y);
        if (pair.first.y == lineY) {
            insertCoordinateIntoMap(objectsInLine, pair.first.x);
        }
        if (pair.first.x + man > maxX) {
            maxX = pair.first.x + man;
        }
        if (pair.first.x - man< minX) {
            minX = pair.first.x - man;
        }
    }

    long offset = abs(minX);
    vector<int> line(maxX-minX);
    long count = 0;

    for (auto &sensorBeaconPair: sensorBeaconList) {
        Sensor sensor = sensorBeaconPair.first;
        Beacon beacon = sensorBeaconPair.second;
        long man = manhattan(sensor.x, sensor.y, beacon.x, beacon.y);

        long x = sensor.x;
        long y = lineY;

        int i = 0;

        while (manhattan(sensor.x, sensor.y, x, y) <= man) {
            if (line.at(x + offset) != 1) {
                line.at(x + offset) = 1;
                count++;
            }
            if (line.at((x - 2*i) + offset) != 1) {
                line.at((x - 2*i) + offset) = 1;
                count++;
            }
            i++;
            x++;
        }
    }

    cout << count - objectsInLine.size();

    return 0;
}