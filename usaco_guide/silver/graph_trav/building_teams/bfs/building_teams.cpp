#include <deque>
#include <iostream>
#include <vector>

using namespace std;

int main() {
	int n;
	int m;
	cin >> n >> m;
	vector<vector<int>> adj(n);
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		adj[--a].push_back(--b);
		adj[b].push_back(a);
	}

	vector<int> assigned(n);
	bool valid = true;
	for (int i = 0; i < n; i++) {
		if (assigned[i] != 0) { continue; }

		assigned[i] = 1;
		deque<int> todo{i};
		while (!todo.empty()) {
			int curr = todo.front();
			todo.pop_front();
			int n_color = assigned[curr] == 1 ? 2 : 1;
			for (int next : adj[curr]) {
				if (assigned[next] != 0) {
					if (assigned[next] != n_color) {
						valid = false;
						goto end;
					}
				} else {
					assigned[next] = n_color;
					todo.push_back(next);
				}
			}
		}
	}
end:;

	if (valid) {
		for (int i = 0; i < n; i++) { cout << assigned[i] << " \n"[i == n - 1]; }
	} else {
		cout << "IMPOSSIBLE" << endl;
	}
}