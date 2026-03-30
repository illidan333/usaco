#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <string>
using namespace std;

int solve(const string& inputFile) {
    ifstream fin(inputFile);

    int N, x;
    fin >> N >> x;

    vector<int> algorithms(N);
    for (int i = 0; i < N; i++) {
        fin >> algorithms[i];
    }

    // read in the input, store the algorithms in a vector, algorithms
    sort(algorithms.begin(), algorithms.end());
    int count = 0;  // number of minutes used so far
    int i = 0;
    while (i < N && count + algorithms[i] <= x) {
        // while there is enough time, learn more algorithms
        count += algorithms[i];
        i++;
    }
    return i;
}

int main() {
    vector<string> testFiles;
    for (const auto& entry : filesystem::directory_iterator("tests")) {
        string path = entry.path().string();
        if (path.size() >= 3 && path.substr(path.size() - 3) == ".in") {
            testFiles.push_back(path);
        }
    }
    sort(testFiles.begin(), testFiles.end());

    int passed = 0, failed = 0;
    for (const string& inFile : testFiles) {
        string outFile = inFile.substr(0, inFile.size() - 3) + ".out";
        
        int result = solve(inFile);
        
        ifstream fout(outFile);
        int expected;
        fout >> expected;
        
        if (result == expected) {
            cout << inFile << ": PASS" << endl;
            passed++;
        } else {
            cout << inFile << ": FAIL (got " << result << ", expected " << expected << ")" << endl;
            failed++;
        }
    }
    
    cout << "\n" << passed << " passed, " << failed << " failed" << endl;
    return failed > 0 ? 1 : 0;
}
