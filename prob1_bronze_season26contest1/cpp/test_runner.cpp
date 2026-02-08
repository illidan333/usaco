#include <bits/stdc++.h>
#include <filesystem>
#include "solution_impl.h"
using namespace std;

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

vector<string> read_expected(const string &path) {
    ifstream in(path);
    vector<string> out;
    string token;
    while (in >> token) {
        out.push_back(token);
    }
    return out;
}

int main(int argc, char **argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    namespace fs = std::filesystem;
    fs::path base_dir = fs::absolute(fs::path(argv[0])).parent_path();
    fs::path test_dir = (base_dir / ".." / "testData").lexically_normal();
    vector<string> files;

    if (!fs::is_directory(test_dir)) {
        cout << "testData folder not found: " << test_dir.string() << "\n";
        return 0;
    }

    for (const auto &entry : fs::directory_iterator(test_dir)) {
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
        fs::path in_path = test_dir / name;
        fs::path out_path = test_dir / (name.substr(0, name.size() - 3) + ".out");

        vector<string> outputs = run_file(in_path.string());
        bool has_expected = fs::exists(out_path);
        vector<string> expected = has_expected ? read_expected(out_path.string()) : vector<string>();

        string status;
        if (!has_expected) {
            status = "MISSING .out";
        } else if (outputs == expected) {
            status = "PASS";
        } else {
            status = "FAIL";
        }

        cout << name << ": " << status << "\n";
    }

    return 0;
}
