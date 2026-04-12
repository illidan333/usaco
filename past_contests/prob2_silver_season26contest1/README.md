# Nuclear Reactor Rod Optimization (USACO Silver)

## Problem Statement

Bessie is designing a nuclear reactor with N fuel rods. Each rod i has:
- A stable operating range [l_i, r_i]
- An energy value a_i (must be an integer within the range to generate power)

There are M constraints of the form: **a_x + a_y = z**

**Goal:** Maximize the number of rods that can generate power while satisfying all constraints.

## Solution Approach

The solution uses a **graph-based DFS algorithm** with constraint propagation:

### Key Insights

1. **Graph Representation:** Constraints form edges in a graph
2. **Connected Components:** Each component can be solved independently
3. **Linear Expressions:** Each rod's energy can be expressed as `a_j = coef × a_representative + constant`
4. **Cycle Detection:** Cycles in the graph may fix certain rod values or create contradictions
5. **Optimization:** Use interval sweep-line algorithm to maximize feasible rods

### Algorithm Overview

```
For each connected component:
  1. DFS from arbitrary node
  2. Express each node as linear function of representative
  3. Check for cycle constraints (may fix values)
  4. Count maximum satisfiable rods:
     - If value fixed: count rods within range
     - If value free: use sweep-line on intervals
```

## Files

- **[solution.cpp](solution.cpp)** - Main C++ solution
- **[test.cpp](test.cpp)** - Test harness with embedded test cases
- **[EXPLANATION.md](EXPLANATION.md)** - Detailed algorithm explanation with Mermaid diagram
- **[1.in - 13.in](1.in)** - Test input files
- **[1.out - 13.out](1.out)** - Expected output files

## Compilation & Testing

### Compile the Solution
```bash
g++ -o solution solution.cpp -std=c++17 -O2
```

### Run with Test Cases
```bash
# Single test
./solution < 1.in

# Run all tests
for i in {1..13}; do
  ./solution < $i.in > output.txt
  diff output.txt $i.out && echo "Test $i: PASS" || echo "Test $i: FAIL"
done
```

## Example Walkthrough

### Test Case 2
```
Input:
3 2
10 -10 10
10 -10 10
1 2 0
2 3 0

Constraints: a_1 + a_2 = 0, a_2 + a_3 = 0
```

**Solution:**
- a_1 = a_3 = 10 (within range [10, 10])
- a_2 = -10 (within range [-10, -10])
- All constraints satisfied: 10 + (-10) = 0 ✓, (-10) + 10 = 0 ✓
- **Answer: 3** (all rods generate power)

## Complexity Analysis

- **Time Complexity:** O((N + M) log(N + M))
  - DFS: O(N + M)
  - Sorting intervals: O(M log M)
- **Space Complexity:** O(N + M) for adjacency list and auxiliary structures

## Implementation Details

### Key Data Structures
- `adj[i]`: Adjacency list of constraints for rod i
- `set_v[i]`: Linear expression for rod i: `(coef, constant)` where `a_i = coef × x + constant`
- `mod`: Interval endpoints for sweep-line algorithm

### Critical Functions
- **DFS:** Explores connected component and propagates constraints
- **Cycle Detection:** Checks if same node reached with conflicting equations
- **Sweep Line:** Finds maximum overlapping intervals for free variables

## Test Results

All 13 test cases pass:
- ✓ Test 1: PASS
- ✓ Test 2: PASS
- ✓ Test 3: PASS
- ... (all tests pass)
- ✓ Test 13: PASS

## Author Notes

This solution handles several challenging cases:
1. **Disconnected components:** Each solved independently
2. **Cycles with constraints:** May fix variable values
3. **Inconsistent constraints:** Detected and returns -1
4. **Free variables:** Optimized using sweep-line algorithm
5. **Large value ranges:** Uses 64-bit integers to avoid overflow
