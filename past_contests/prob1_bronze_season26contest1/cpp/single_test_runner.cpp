#define INCLUDED_IN_TEST
#include "solution.cpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

static vector<long long> read_numbers(const string &path) {
    ifstream in(path);
    vector<long long> values;
    long long x;
    while (in >> x) {
        values.push_back(x);
    }
    return values;
}

static vector<long long> parse_single_case(const vector<long long> &values) {
    if (values.size() == 5) {
        return {values[0], values[1], values[2], values[3], values[4]};
    }
    if (values.size() >= 6) {
        long long t = values[0];
        if (t <= 0) {
            throw runtime_error("T must be positive when provided");
        }
        return {values[1], values[2], values[3], values[4], values[5]};
    }
    throw runtime_error("Expected 5 numbers or T followed by 5 numbers");
}

int main(int argc, char **argv) {
    string path = (argc > 1) ? argv[1] : string("single_test_input.txt");
    ifstream check(path);
    if (!check.good()) {
        cout << "Input file not found: " << path << "\n";
        if (path == "single_test_input.txt") {
            cout << "Create it and paste numbers like: 2 3 1 1 6\n";
        }
        return 0;
    }

    vector<long long> values = read_numbers(path);
    if (values.empty()) {
        cout << "Input file is empty: " << path << "\n";
        return 0;
    }

    vector<long long> args_case = parse_single_case(values);
    long long result = solve_case(args_case[0], args_case[1], args_case[2], args_case[3], args_case[4]);
    cout << result << "\n";
    return 0;
}
