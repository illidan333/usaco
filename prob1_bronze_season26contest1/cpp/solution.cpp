#include <bits/stdc++.h>
#include "solution_impl.h"
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) {
        return 0;
    }
    while (t--) {
        ll a, b, c_a, c_b, f_a;
        cin >> a >> b >> c_a >> c_b >> f_a;
        cout << solve_case(a, b, c_a, c_b, f_a) << "\n";
    }
    return 0;
}
