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
        
        // Generate actual output
        string actualOutput;
        int numTestCases;
        inputFile >> numTestCases;
        
        while (numTestCases--) {
            int numRods, numConstraints;
            inputFile >> numRods >> numConstraints;
            
            vector<ll> lowerBound(numRods), upperBound(numRods);
            for (ll &bound : lowerBound) inputFile >> bound;
            for (ll &bound : upperBound) inputFile >> bound;
            
            vector<vector<pair<int, ll>>> adjacencyList(numRods);
            for (int c = 0; c < numConstraints; c++) {
                int rod1, rod2;
                ll constraintValue;
                inputFile >> rod1 >> rod2 >> constraintValue;
                rod1--; rod2--;  // Convert to 0-indexed
                adjacencyList[rod1].push_back({rod2, constraintValue});
                adjacencyList[rod2].push_back({rod1, constraintValue});
            }
            
            int result = solveCase(numRods, numConstraints, lowerBound, upperBound, adjacencyList);
            actualOutput += to_string(result) + "\n";
        }
        inputFile.close();
        
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
