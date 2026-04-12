#include <iostream>
#include <queue>

using namespace std;

int main() {
    priority_queue<int> pq;
    pq.push(7);                // [7]
    pq.push(2);                // [2, 7]
    pq.push(1);                // [1, 2, 7]
    pq.push(5);                // [1, 2, 5, 7]
    cout << pq.top() << endl;  // 7
    pq.pop();                  // [1, 2, 5]
    pq.pop();                  // [1, 2]
    pq.push(6);                // [1, 2, 6]//
    // Created by hippo on 4/11/2026.
    //
}