#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

vector<int> p;
vector<int> ans;
bool in_cycle = false;

void dfs(int n) {
    if (ans[n] != -2) {
        // it seems we've come back to something we've visited- a cycle!
        if (ans[n] == -1) {
            in_cycle = true;
            ans[n] = n;
        }
        return;  // either way, this one's already been processed
    }

    ans[n] = -1;  // set a marker for our dfs

    dfs(p[n]);
    // check if we're back at the initial cycle node
    if (ans[n] != -1) {
        // if so, now we're no longer in the cycle
        in_cycle = false;
    } else {
        // set our answer depending on if we're in a cycle or not
        ans[n] = in_cycle ? n : ans[p[n]];
    }
}

int main() {
    int n;
    std::cin >> n;
    p = vector<int>(n);
    for (int &i : p) {
        std::cin >> i;
        i--;
    }

    ans = vector<int>(n, -2);  // -2 is our initial no-answer value
    for (int i = 0; i < n; i++) {
        // in_cycle is always reset to false at the end of each DFS
        dfs(i);
    }

    for (int i = 0; i < n; i++) { cout << (ans[i] + 1) << " \n"[i == n - 1]; }
}