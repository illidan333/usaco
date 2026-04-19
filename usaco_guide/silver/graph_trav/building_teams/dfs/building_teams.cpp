#include <iostream>
#include <vector>

using namespace std;

vector<int> assigned;
vector<vector<int>> adj;

/** @return true only if it's possible to assign each person to a team */
bool dfs(int node) {
	int curr = assigned[node];
	int nColor = curr == 1 ? 2 : 1;  // The color the neighbors should be
	for (int n : adj[node]) {
		if (assigned[n] != 0) {
			// Check if the already existing color lines up
			if (assigned[n] != nColor) { return false; }
		} else {
			assigned[n] = nColor;
			if (!dfs(n)) {
				return false;  // We stop as soon as we hit a contradiction
			}
		}
	}
	return true;
}

int main() {
	int n;
	int m;
	cin >> n >> m;
	adj = vector<vector<int>>(n);
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		adj[--a].push_back(--b);
		adj[b].push_back(a);
	}

	assigned = vector<int>(n);
	bool valid = true;
	for (int i = 0; i < n; i++) {
		if (assigned[i] == 0) {
			assigned[i] = 1;  // Assign an arbitrary starting team
			if (!dfs(i)) {
				valid = false;
				break;
			}
		}
	}

	if (valid) {
		for (int i = 0; i < n; i++) { cout << assigned[i] << " \n"[i == n - 1]; }
	} else {
		cout << "IMPOSSIBLE" << endl;
	}
}