#define INCLUDED_IN_TEST
#include "solution.cpp"
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
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

int main(int argc, char **argv) {
    string path = (argc > 1) ? argv[1] : string("single_test_input.txt");
    ifstream check(path);
    if (!check.good()) {
        cout << "Input file not found: " << path << "\n";
        if (path == "single_test_input.txt") {
            cout << "Create it and paste input like: 4 2 3 2 2 11 3 4 3 3 1 100\n";
        }
        return 0;
    }

    vector<long long> values = read_numbers(path);
    if (values.size() < 5) {
        cout << "Input file does not contain enough values: " << path << "\n";
        return 0;
    }

    int n = static_cast<int>(values[0]);
    int k = static_cast<int>(values[1]);

    vector<tuple<int, int, ll>> updates;
    if (values.size() >= 3) {
        long long q = values[2];
        size_t expected = 3 + static_cast<size_t>(q) * 3;
        if (values.size() == expected) {
            updates.reserve(static_cast<size_t>(q));
            size_t idx = 3;
            for (long long i = 0; i < q; i++) {
                int r = static_cast<int>(values[idx++]) - 1;
                int c = static_cast<int>(values[idx++]) - 1;
                ll v = values[idx++];
                updates.emplace_back(r, c, v);
            }
        } else if ((values.size() - 2) % 3 == 0) {
            long long inferred = static_cast<long long>((values.size() - 2) / 3);
            updates.reserve(static_cast<size_t>(inferred));
            size_t idx = 2;
            for (long long i = 0; i < inferred; i++) {
                int r = static_cast<int>(values[idx++]) - 1;
                int c = static_cast<int>(values[idx++]) - 1;
                ll v = values[idx++];
                updates.emplace_back(r, c, v);
            }
        } else {
            cout << "Input does not match expected format (N K Q followed by Q updates).\n";
            return 0;
        }
    }

    vector<ll> outputs = solve_all(n, k, updates);
    for (ll value : outputs) {
        cout << value << "\n";
    }
    return 0;
}
