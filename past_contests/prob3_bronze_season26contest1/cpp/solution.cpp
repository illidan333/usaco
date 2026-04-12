#include <bits/stdc++.h>
using namespace std;

using ll = long long;

vector<ll> solve_all(int n, int k, const vector<tuple<int, int, ll>> &updates) {
    int size = n - k + 1;
    vector<vector<ll>> square_sum(size, vector<ll>(size, 0));
    vector<vector<ll>> grid(n, vector<ll>(n, 0));

    ll max_sum = 0;
    vector<ll> outputs;
    outputs.reserve(updates.size());

    for (const auto &update : updates) {
        int r, c;
        ll v;
        tie(r, c, v) = update;
        ll delta = v - grid[r][c];
        grid[r][c] = v;

        int r_start = max(0, r - k + 1);
        int r_end = min(r, n - k);
        int c_start = max(0, c - k + 1);
        int c_end = min(c, n - k);

        for (int i = r_start; i <= r_end; i++) {
            for (int j = c_start; j <= c_end; j++) {
                ll new_sum = (square_sum[i][j] += delta);
                if (new_sum > max_sum) {
                    max_sum = new_sum;
                }
            }
        }
        outputs.push_back(max_sum);
    }

    return outputs;
}

#ifndef INCLUDED_IN_TEST
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    if (!(cin >> n >> k)) {
        return 0;
    }
    int q;
    cin >> q;
    vector<tuple<int, int, ll>> updates;
    updates.reserve(q);
    for (int i = 0; i < q; i++) {
        int r, c;
        ll v;
        cin >> r >> c >> v;
        updates.emplace_back(r - 1, c - 1, v);
    }

    vector<ll> outputs = solve_all(n, k, updates);
    for (ll value : outputs) {
        cout << value << "\n";
    }
    return 0;
}
#endif
