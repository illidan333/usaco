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

	vector<bool> visited(n);
	vector<int> city_reps;
	for (int i = 0; i < n; i++) {
		if (visited[i]) { continue; }

		visited[i] = true;
		city_reps.push_back(i);
		deque<int> todo{i};
		while (!todo.empty()) {
			int curr = todo.front();
			todo.pop_front();
			for (int next : adj[curr]) {
				if (!visited[next]) {
					visited[next] = true;
					todo.push_back(next);
				}
			}
		}
	}

	cout << city_reps.size() - 1 << '\n';
	for (int i = 0; i < city_reps.size() - 1; i++) {
		cout << city_reps[i] + 1 << ' ' << city_reps[i + 1] + 1 << '\n';
	}
}