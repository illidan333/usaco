#define INCLUDED_IN_TEST
#include "solution.cpp"

int main() {
    int passedTests = 0, failedTests = 0;
    
    // Run all 13 test cases
    for (int testNum = 1; testNum <= 13; testNum++) {
        ifstream inputFile(to_string(testNum) + ".in");
        ifstream outputFile(to_string(testNum) + ".out");
        
        if (!inputFile || !outputFile) {
            cout << "Test " << testNum << ": ✗ File error\n";
            failedTests++;
            continue;
        }
        
        // Read expected output
        string expectedOutput((istreambuf_iterator<char>(outputFile)), istreambuf_iterator<char>());
        outputFile.close();
        
        // Read input data
        stringstream buffer;
        buffer << inputFile.rdbuf();
        string inputData = buffer.str();
        inputFile.close();
        
        // Redirect cin/cout
        istringstream iss(inputData);
        ostringstream oss;
        streambuf* cinbuf = cin.rdbuf();
        streambuf* coutbuf = cout.rdbuf();
        cin.rdbuf(iss.rdbuf());
        cout.rdbuf(oss.rdbuf());
        
        // Run solve() for each test case
        int T;
        cin >> T;
        while (T--) solve();
        
        // Restore cin/cout
        cin.rdbuf(cinbuf);
        cout.rdbuf(coutbuf);
        
        string actualOutput = oss.str();
        
        // Compare outputs
        if (actualOutput == expectedOutput) {
            cout << "Test " << testNum << ": ✓ PASSED\n";
            passedTests++;
        } else {
            cout << "Test " << testNum << ": ✗ FAILED\n";
            failedTests++;
        }
    }
    
    cout << "\nResults: " << passedTests << " passed, " << failedTests << " failed\n";
    return failedTests == 0 ? 0 : 1;
}
