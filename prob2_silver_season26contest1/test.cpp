#include "solution.cpp"

int main() {
    int passed = 0, failed = 0;
    
    for (int i = 1; i <= 13; i++) {
        ifstream in(to_string(i) + ".in"), out(to_string(i) + ".out");
        if (!in || !out) { cout << "Test " << i << ": ✗ File error\n"; failed++; continue; }
        
        string expected((istreambuf_iterator<char>(out)), istreambuf_iterator<char>());
        out.close();
        
        string actual;
        int T;
        in >> T;
        while (T--) {
            int n, m;
            in >> n >> m;
            vector<ll> l(n), r(n);
            for (ll &x : l) in >> x;
            for (ll &x : r) in >> x;
            vector<vector<pair<int, ll>>> adj(n);
            while (m--) {
                int x, y;
                ll z;
                in >> x >> y >> z;
                adj[x-1].push_back({y-1, z});
                adj[y-1].push_back({x-1, z});
            }
            actual += to_string(solveCase(n, m, l, r, adj)) + "\n";
        }
        in.close();
        
        if (actual == expected) {
            cout << "Test " << i << ": ✓ PASSED\n";
            passed++;
        } else {
            cout << "Test " << i << ": ✗ FAILED\n";
            failed++;
        }
    }
    
    cout << "\nResults: " << passed << " passed, " << failed << " failed\n";
    return failed == 0 ? 0 : 1;
}
