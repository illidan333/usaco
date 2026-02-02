#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int solveCase(int n, int m, vector<ll>& l, vector<ll>& r, vector<vector<pair<int, ll>>>& adj);

int solveCase(int n, int m, vector<ll>& l, vector<ll>& r, vector<vector<pair<int, ll>>>& adj) {
    bool isImpossible = false;
    auto markImpossible = [&]() { isImpossible = true; };

    vector<bool> visited(n);
    vector<pair<int, ll>> expr(n);  // (coefficient, constant): a[i] = coef*x + constant
    int totalRods = 0;

    // Process each connected component independently
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            bool hasFixedValue = false;
            ll fixedValue;
            vector<pair<ll, int>> intervals;

            // DFS: express node in terms of representative variable
            auto dfs = [&](auto self, int i, pair<int, ll> v) -> void {
                if (visited[i]) {
                    // Cycle: check consistency
                    if (expr[i].first == v.first) {
                        if (expr[i].second != v.second) markImpossible();
                    } else {
                        // Solve: expr[i].first*x + expr[i].second = v.first*x + v.second
                        ll x = expr[i].first * expr[i].second + v.first * v.second;
                        x *= -1;
                        if (x & 1) markImpossible();
                        else {
                            x /= 2;
                            if (!hasFixedValue) hasFixedValue = true, fixedValue = x;
                            else if (x != fixedValue) markImpossible();
                        }
                    }
                } else {
                    // Record interval where rod can generate power
                    if (v.first == 1) {
                        intervals.push_back({l[i] - v.second, 1});
                        intervals.push_back({1 + r[i] - v.second, -1});
                    } else {
                        intervals.push_back({v.second - r[i], 1});
                        intervals.push_back({1 + v.second - l[i], -1});
                    }
                    visited[i] = true;
                    expr[i] = v;
                    for (auto [j, x] : adj[i])
                        self(self, j, {-v.first, x - v.second});
                }
            };
            dfs(dfs, i, {1, 0});

            // Count maximum feasible rods
            if (hasFixedValue) {
                for (auto [x, y] : intervals)
                    if (x <= fixedValue) totalRods += y;
            } else {
                sort(intervals.begin(), intervals.end());
                int cur = 0, opt = 0;
                for (auto [x, y] : intervals) opt = max(opt, cur += y);
                totalRods += opt;
            }
        }
    }

    return isImpossible ? -1 : totalRods;
}

void solve() {
    int n, m;
    cin >> n >> m;

    vector<ll> l(n), r(n);
    for (ll &i : l) cin >> i;
    for (ll &i : r) cin >> i;

    vector<vector<pair<int, ll>>> adj(n);
    while (m--) {
        int i, j;
        ll x;
        cin >> i >> j >> x;
        i--; j--;
        adj[i].push_back({j, x});
        adj[j].push_back({i, x});
    }

    cout << solveCase(n, m, l, r, adj) << "\n";
}

#ifndef INCLUDED_IN_TEST
int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}
#endif
