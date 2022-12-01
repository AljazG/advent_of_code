using namespace std;

namespace string_utils
{
    bool isBlank(string x) {
       return x.empty() || x.find_first_not_of(' ') == string::npos;
    }
}
