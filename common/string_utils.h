#import <sstream>
#import <vector>
#include <fstream>

using namespace std;

namespace string_utils
{
    bool isBlank(string &x) {
       return x.empty() || x.find_first_not_of(' ') == string::npos;
    }

    vector<string> split(string &s, string &delimiter) {
        size_t pos_start = 0, pos_end, delim_len = delimiter.length();
        string token;
        vector<string> res;

        while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
            token = s.substr (pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            res.push_back (token);
        }
        res.push_back (s.substr (pos_start));
        return res;
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
