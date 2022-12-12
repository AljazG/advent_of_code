#include <list>
#include <unordered_map>
#include "../common/input_utils.h"
#include "../common/string_utils.h"
#include "../common/grid_utils.h"

struct Monkey {
    int id{};
    list<long long> items;
    char operation{};
    int multiplier = 0;
    long inspections = 0;
    int divisor{};
    int passMonkey{};
    int failMonkey{};
};

void constructMonkeyMap(vector<string> &input, unordered_map<int, Monkey *> &monkeys) {
    int i = 0;

    while (i < input.size()) {
        string monkeyNum = string_utils::split(input.at(i))[1];
        monkeyNum.erase(monkeyNum.size() - 1);

        string startingItemsLine = input.at(i + 1);
        startingItemsLine.erase(0, 17);
        vector<string> startingItems = string_utils::split(startingItemsLine, ",");

        string operationLine = input.at(i + 2);
        operationLine.erase(0, 23);

        string divisor = input.at(i + 3);
        divisor.erase(0, 20);

        string passMonkey = input.at(i + 4);
        passMonkey.erase(0, 29);

        string failMonkey = input.at(i + 5);
        failMonkey.erase(0, 30);


        auto *monkey = new Monkey;
        monkey->id = stoi(monkeyNum);

        for (auto &item: startingItems) {
            monkey->items.push_back(stoi(item));
        }
        monkey->operation = operationLine.at(0);
        operationLine.erase(0, 2);

        if (operationLine != "old") {
            monkey->multiplier = stoi(operationLine);
        }

        monkey->divisor = stoi(divisor);
        monkey->failMonkey = stoi(failMonkey);
        monkey->passMonkey = stoi(passMonkey);

        monkeys.insert({stoi(monkeyNum), monkey});
        i += 7;
    }
}

int main() {

    vector<string> input = input_utils::readLines("../data/day11/input.txt");
    unordered_map<int, Monkey *> monkeys;

    constructMonkeyMap(input, monkeys);

    int divisor = 1;

    for (auto &monkey: monkeys) {
        divisor *= monkey.second->divisor;
    }

    int i = 0;

    // first = 20
    while (i < 10000) {
        ++i;
        cout << "\nround " << i << "\n";

        for (int j = 0; j < monkeys.size(); j++) {
            Monkey *monkey = monkeys.at(j);
            for (auto &item: monkey->items) {

                if (monkey->operation == '*') {
                    if (monkey->multiplier != 0) {
                        item *= monkey->multiplier;
                    } else {
                        item *= item;
                    }
                } else if (monkey->operation == '+') {
                    if (monkey->multiplier != 0) {
                        item += monkey->multiplier;
                    } else {
                        item += item;
                    }
                }

                // first
//                item /= 3;

                //second
                item %= divisor;

                if (item % (monkey->divisor) == 0) {
                    monkeys.at(monkey->passMonkey)->items.push_back(item);
                } else {
                    monkeys.at(monkey->failMonkey)->items.push_back(item);
                }
                monkey->inspections++;
            }
            monkey->items.clear();
        }

    }

    list<long long> inspections;

    cout << "Inspections:\n";
    for (auto &monke: monkeys) {
        cout << monke.second->id << ": " << monke.second->inspections << "\n";
        inspections.push_back(monke.second->inspections);
    }

    inspections.sort();

    long long out = 1;

    for (auto it = prev(inspections.end(), 1); it != prev(inspections.end(), 3); --it) {
        out *= *it;
    }

    cout << "\nMonkey business: " << out;

    return 0;
}