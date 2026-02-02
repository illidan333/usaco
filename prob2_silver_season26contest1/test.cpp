#include <bits/stdc++.h>
#include <cassert>
using namespace std;

typedef long long ll;

// Solution logic extracted from solution.cpp for debugging
void solveHelper(
    int n, int m,
    vector<ll> l, vector<ll> r,
    vector<vector<pair<int, ll>>>& adj,
    int& result
) {
    bool imp = false;
    auto no = [&]() { imp = true; };

    vector<bool> done(n);
    vector<pair<int, ll>> set_v(n);
    int ans = 0;

    for (int i = 0; i < n; i++) {
        if (!done[i]) {
            bool has_set = false;
            ll set_x;
            vector<pair<ll, int>> mod;

            auto dfs = [&](auto self, int i, pair<int, ll> v) -> void {
                if (done[i]) {
                    if (set_v[i].first == v.first) {
                        if (set_v[i].second != v.second) no();
                    } else {
                        ll x = set_v[i].first * set_v[i].second +
                               v.first * v.second;
                        x *= -1;
                        if (x & 1) no();
                        else {
                            x /= 2;
                            if (!has_set) has_set = true, set_x = x;
                            else if (x != set_x) no();
                        }
                    }
                } else {
                    if (v.first == 1) {
                        mod.push_back({l[i] - v.second, 1});
                        mod.push_back({1 + r[i] - v.second, -1});
                    } else {
                        mod.push_back({v.second - r[i], 1});
                        mod.push_back({1 + v.second - l[i], -1});
                    }
                    done[i] = true;
                    set_v[i] = v;
                    for (auto [j, x] : adj[i])
                        self(self, j, {-v.first, x - v.second});
                }
            };
            dfs(dfs, i, {1, 0});

            if (has_set) {
                for (auto [x, y] : mod)
                    if (x <= set_x) ans += y;
            } else {
                sort(mod.begin(), mod.end());
                int cur = 0, opt = 0;
                for (auto [x, y] : mod) opt = max(opt, cur += y);
                ans += opt;
            }
        }
    }

    result = imp ? -1 : ans;
}

int main() {
    // Load and run all 13 test cases from 1.in - 13.in files
    
    cout << "Running all 13 test cases...\n\n";
    
    int passed = 0, failed = 0;
    
    for (int test_num = 1; test_num <= 13; test_num++) {
        string in_file = to_string(test_num) + ".in";
        string out_file = to_string(test_num) + ".out";
        
        // Read input file
        ifstream in(in_file);
        if (!in.is_open()) {
            cout << "Test " << test_num << ": ✗ FAILED (Cannot open " << in_file << ")\n";
            failed++;
            continue;
        }
        
        int T;
        in >> T;
        
        // Read expected output file
        ifstream out(out_file);
        if (!out.is_open()) {
            cout << "Test " << test_num << ": ✗ FAILED (Cannot open " << out_file << ")\n";
            failed++;
            in.close();
            continue;
        }
        
        string expected_output;
        string line;
        while (getline(out, line)) {
            expected_output += line + "\n";
        }
        out.close();
        
        // Run test cases
        string actual_output;
        while (T--) {
            int n, m;
            in >> n >> m;
            
            vector<ll> l(n), r(n);
            for (ll &i : l) in >> i;
            for (ll &i : r) in >> i;
            
            vector<vector<pair<int, ll>>> adj(n);
            while (m--) {
                int i, j;
                ll x;
                in >> i >> j >> x;
                i--; j--;
                adj[i].push_back({j, x});
                adj[j].push_back({i, x});
            }
            
            int result = 0;
            solveHelper(n, m, l, r, adj, result);
            actual_output += to_string(result) + "\n";
        }
        
        in.close();
        
        // Compare output
        if (actual_output == expected_output) {
            cout << "Test " << test_num << ": ✓ PASSED\n";
            passed++;
        } else {
            cout << "Test " << test_num << ": ✗ FAILED\n";
            cout << "  Expected: " << expected_output;
            cout << "  Got:      " << actual_output;
            failed++;
        }
    }
    
    cout << "\n========================================\n";
    cout << "Results: " << passed << " passed, " << failed << " failed\n";
    cout << "========================================\n";
    
    return failed == 0 ? 0 : 1;
}
