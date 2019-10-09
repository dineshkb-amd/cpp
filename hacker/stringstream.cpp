#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

vector<int> parseInts(string str) {
    vector<int> all;
    std::stringstream ss(str);

    while (!ss.eof()) {
        int n;
        char ch;

        ss >> n >> ch; 

        all.push_back(n);
    }

    return all;
}

int main() {
    string str;
    cin >> str;

    vector<int> integers = parseInts(str);
    for(int i = 0; i < integers.size(); i++) {
        cout << integers[i] << "\n";
    }
    
    return 0;
}
