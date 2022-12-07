#import <sstream>
#import<vector>
#include <fstream>

using namespace std;

namespace string_utils
{
    bool isBlank(string &x) {
       return x.empty() || x.find_first_not_of(' ') == string::npos;
    }

    vector<string> split(string &x) {
        vector<string> out;
        stringstream ss(x);
        string element;

        while(getline(ss, element,' ')) {
            out.push_back(element);
        }
        return out;
    }
}
