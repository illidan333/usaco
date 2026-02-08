#include <bits/stdc++.h>
#include <filesystem>
using namespace std;

using ll = long long;

ll solve_case(ll a, ll b, ll c_a, ll c_b, ll f_a) {
    ll initial_a = (b / c_b) * c_a + a;
    if (initial_a >= f_a) {
        return 0;
    }

    ll need_a = f_a - 1 - initial_a;
    ll y = c_b - 1 - (b % c_b);

    if (c_a >= c_b) {
        y += need_a;
    } else {
        y += (need_a / c_a) * c_b + (need_a % c_a);
    }

    return y + 1;
}

vector<string> run_file(const string &path) {
    ifstream in(path);
    vector<string> out;
    int t;
    if (!(in >> t)) {
        return out;
    }
    for (int i = 0; i < t; i++) {
        ll a, b, c_a, c_b, f_a;
        in >> a >> b >> c_a >> c_b >> f_a;
        out.push_back(to_string(solve_case(a, b, c_a, c_b, f_a)));
    }
    return out;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string test_dir = "..\\testData";
    vector<string> files;

    for (const auto &entry : std::filesystem::directory_iterator(test_dir)) {
        if (!entry.is_regular_file()) {
            continue;
        }
        string name = entry.path().filename().string();
        if (name.size() >= 3 && name.substr(name.size() - 3) == ".in") {
            files.push_back(name);
        }
    }

    sort(files.begin(), files.end(), [](const string &a, const string &b) {
        if (a.size() != b.size()) {
            return a.size() < b.size();
        }
        return a < b;
    });

    for (const string &name : files) {
        string path = test_dir + "\\" + name;
        vector<string> outputs = run_file(path);
        cout << name << ":\n";
        for (const string &line : outputs) {
            cout << line << "\n";
        }
        cout << "-\n";
    }

    return 0;
}
