# USACO Solution Coding Guidelines

## Core Principles
- **Conciseness**: Write compact, efficient code. Refer to EXPLANATION.md for understanding complex logic.
- **Clarity**: Variable names and logic must be immediately understandable.
- **Correctness**: All 13 test cases must pass.

## Code Structure

### Function Design
- **Max 100 lines** per function (split longer functions into helpers)
- **Single responsibility**: Each function does one thing well
- Document parameters and return values with inline comments for complex logic
- Use descriptive names: prefer `solveCase()` over `solve2()`, `cycleDetection()` over `checkCycle()`

### Variable Naming
- **Descriptive names**: `adjacencyList`, `visited`, `intervals`, not `adj`, `v`, `mod`
- **Exception**: Single letters for loop counters (`i`, `j`, `k`) are acceptable
- **Constants**: UPPER_CASE (e.g., `MAX_NODES`, `INF`)
- **Types**: Prefix boolean flags with `is` or `has` (e.g., `has_set`, `is_fixed`)

### Type Safety
- **Use `long long`** for constraint values to avoid overflow (competitive programming)
- **Explicit types** over `auto` — exception: obvious container iterators
- **Avoid `int`** for results that could exceed 2^31-1
- Example: `vector<ll> ranges(n);` not `vector<int> ranges(n);`

## Documentation

### Complex Algorithms
- Graph-based DFS: explain how linear expressions are computed
- Cycle detection: document how fixed values are derived
- Sweep-line: clarify how intervals are processed
- **Reference**: See [EXPLANATION.md](../prob2_silver_season26contest1/EXPLANATION.md) for detailed walkthrough with Mermaid diagrams

### Code Comments
```cpp
// Bad
int x = set_v[i].first * set_v[i].second + v.first * v.second;

// Good
// Solve: c1*x + b1 = c2*x + b2 → (c1-c2)*x = b2-b1
ll x = set_v[i].first * set_v[i].second + v.first * v.second;
```

## C++ Specifics

### Allowed
- `#include <bits/stdc++.h>` (acceptable for USACO)
- Lambda functions for local scope DFS
- Structured bindings (`auto [a, b] = pair;`)
- Modern C++17+ features

### Preferred
- `vector` over raw arrays
- `const` and references for efficiency
- `pair<int, ll>` for coefficient-constant pairs
- Early returns to reduce nesting

### Avoid
- Magic numbers (define as constants)
- Deep nesting (refactor into functions)
- Redundant variables
- `goto` statements

## Testing & Validation
- All 13 test cases in `1.in - 13.in` must pass
- Compile with: `g++ -std=c++17 -O2 solution.cpp -o solution`
- No warnings or errors

## Example: Good USACO Code
```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Solves one test case using graph DFS
int solveCase(int n, int m, vector<ll>& l, vector<ll>& r, 
              vector<vector<pair<int, ll>>>& adj) {
    bool isImpossible = false;
    auto markImpossible = [&]() { isImpossible = true; };
    
    vector<bool> visited(n);
    vector<pair<int, ll>> expr(n);  // (coef, constant)
    int result = 0;
    
    // Process each connected component
    for (int i = 0; i < n; i++) {
        if (visited[i]) continue;
        
        bool hasFixedValue = false;
        ll fixedValue;
        vector<pair<ll, int>> intervals;
        
        // DFS to express all nodes as: value = coef*x + constant
        function<void(int, pair<int, ll>)> dfs = [&](int node, pair<int, ll> formula) {
            if (visited[node]) {
                // Check consistency (detailed in EXPLANATION.md)
                if (expr[node].first == formula.first) {
                    if (expr[node].second != formula.second) markImpossible();
                } else {
                    // Solve linear equation for fixed value
                    ll num = formula.second - expr[node].second;
                    if (num % 2 != 0) markImpossible();
                    else {
                        ll x = num / 2;
                        if (!hasFixedValue) {
                            hasFixedValue = true;
                            fixedValue = x;
                        } else if (x != fixedValue) {
                            markImpossible();
                        }
                    }
                }
            } else {
                // Record interval where this rod can generate power
                visited[node] = true;
                expr[node] = formula;
                
                if (formula.first == 1) {
                    intervals.push_back({l[node] - formula.second, 1});
                    intervals.push_back({1 + r[node] - formula.second, -1});
                } else {
                    intervals.push_back({formula.second - r[node], 1});
                    intervals.push_back({1 + formula.second - l[node], -1});
                }
                
                for (auto [next, weight] : adj[node]) {
                    dfs(next, {-formula.first, weight - formula.second});
                }
            }
        };
        
        dfs(i, {1, 0});
        
        // Compute maximum feasible rods in this component
        if (hasFixedValue) {
            for (auto [x, delta] : intervals) {
                if (x <= fixedValue) result += delta;
            }
        } else {
            sort(intervals.begin(), intervals.end());
            int active = 0, best = 0;
            for (auto [x, delta] : intervals) {
                best = max(best, active += delta);
            }
            result += best;
        }
    }
    
    return isImpossible ? -1 : result;
}
```

## References
- Algorithm explanation: [EXPLANATION.md](../prob2_silver_season26contest1/EXPLANATION.md)
- Visual examples with Mermaid: [EXPLANATION.md](../prob2_silver_season26contest1/EXPLANATION.md)
- Test harness: [test.cpp](../prob2_silver_season26contest1/test.cpp)
