//
// Created by hippo on 4/11/2026.
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;

int main() {
    int N;
    cin >> N;

    vector<int> ans(N);
    vector<pair<pair<int, int>, int>> v(N);

    v.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> v[i].first.first >> v[i].first.second;
        v[i].second = i;  // store the original index
    }
    sort(v.begin(), v.end());

    int last_room = 0;
    using Room = pair<int, int>;
    // min heap to store departure times.
    priority_queue<Room, vector<Room>, greater<Room>> pq;
    for (int i = 0; i < N; i++) {
        if (pq.empty() || pq.top().first >= v[i].first.first) {
            last_room++;
            pq.push(make_pair(v[i].first.second, last_room));
            ans[v[i].second] = last_room;
        } else {
            // accessing the minimum departure time
            Room minimum = pq.top();
            pq.pop();
            pq.push(make_pair(v[i].first.second, minimum.second));
            ans[v[i].second] = minimum.second;
        }
    }

    cout << last_room << "\n";
    for (int i = 0; i < N; i++) { cout << ans[i] << " "; }
}