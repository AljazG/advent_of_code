#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

namespace input_utils {
    vector<string> readLines(const char *fileLocation) {
        vector<string> lines;
        ifstream file;
        file.open(fileLocation);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                lines.push_back(line);
            }
        }
        file.close();
        return lines;
    }

    string readLinesConcat(const char *fileLocation) {
        vector<string> lines = readLines(fileLocation);
        string concat;
        for (string &line: lines) {
            concat += line;
        }
        return concat;
    }

}
