#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   

    int size, nArrays, nQueries;
    
    cin >> nArrays >> nQueries;

    int **arrays = new int*[nArrays];

    for (int i = 0; i < nArrays; i++) {
        cin >> size;
        arrays[i] = new int [size];
        for (int j = 0; j < size; j++) {
            cin >> arrays[i][j];
            cout << "Adding elem @ " << i << "," << j << " to " << arrays[i][j] << "\n";
        }
        cout <<  size << "\n";
        for (int j = 0; j < size; j++) {
            cout << arrays[0][j] << " ";
        }
    }

    for (int i = 0; i < nQueries; i++) {
        int arrayId, elemId;

        cin >> arrayId >> elemId;

        cout << arrays[arrayId][elemId] << "\n";
    }
    return 0;
}
