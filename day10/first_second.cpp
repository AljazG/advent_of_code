#include <list>
#include "../common/input_utils.h"
#include "../common/string_utils.h"
#include "../common/grid_utils.h"

int main() {

    vector<string> input = input_utils::readLines("../data/day10/input.txt");

    stack<string> commands;

    for (int i = (int) input.size() - 1; i >= 0; --i) {
        commands.push(input.at(i));
    }

    bool executing = false;
    int cycleCount = 0;
    long X = 1;
    long signalStrengthSum = 0;

    long addToNextCycle = 0;

    int rows = 6;
    int cols = 40;
    char **grid = grid_utils::constructGridChar(rows, cols);
    grid_utils::fillGrid('.', grid, rows, cols);

    while (!commands.empty() || executing) {

        int i = cycleCount / 40;
        int j = cycleCount % 40;

        if (j >= X - 1 && j <= X + 1) {
            grid[i][j] = '#';
        }

        cycleCount++;

        if (cycleCount == 20 || (cycleCount - 20) % 40 == 0) {
            signalStrengthSum += (cycleCount * X);
            cout << "Cycle num: " << cycleCount << " X: " << X << " Signal strenght: " << (cycleCount * X) << "\n";
        }

        if (executing) {
            X += addToNextCycle;
            addToNextCycle = 0;
            executing = false;
            continue;
        }

        string command = commands.top();
        commands.pop();
        vector<string> split = ::string_utils::split(command);

        if (split[0] == "addx") {
            executing = true;
            addToNextCycle = stol(split[1]);
        }

    }

    cout << "Sum: " << signalStrengthSum << "\n";

    grid_utils::printGrid(grid, rows, cols);

    return 0;
}