# Solution Summary

This file has been moved to the problem folder:

/workspaces/usaco/prob2_silver_season26contest1/SOLUTION_SUMMARY.md

Please open that file for usage and test-run instructions.

# Solution Summary

## Overview
This directory contains a complete solution to the USACO Silver problem about optimizing nuclear reactor rod energy values.

## Files Created

### 1. **solution.cpp** (Main Solution)
   - Fully commented C++ implementation
   - Uses DFS for constraint propagation
   - Implements sweep-line algorithm for interval optimization
   - Handles all edge cases: cycles, contradictions, fixed/free variables
   - Passes all 13 test cases

### 2. **test.cpp** (Test Code)
   - Embedded test harness with predefined test cases
   - Compares output against expected results
   - Can be extended for custom test cases

### 3. **README.md** (Documentation)
   - Problem statement and approach explanation
   - Compilation and testing instructions
   - Example walkthrough with detailed explanation
   - Complexity analysis

### 4. **EXPLANATION.md** (Algorithm Explanation)
   - Detailed algorithm steps with pseudocode
   - Mermaid flowchart showing algorithm flow
   - Example walkthrough of test case 2
   - Complexity breakdown

## How The Solution Works

### Problem Structure
- Each rod needs an integer energy value a_i in range [l_i, r_i] to generate power
- Constraints link pairs of rods: a_x + a_y = z
- Goal: Maximize power-generating rods

### Solution Strategy

1. **Model as Graph**
   - Nodes = rods
   - Edges = constraints

2. **Process Connected Components**
   - Each component solved independently
   - Pick representative node for each component

3. **Express All as Linear Function**
   - For component representative x: a_x = free variable
   - For any other rod j: a_j = coef × a_x + constant
   - Where coef ∈ {-1, +1}

4. **Detect Cycles**
   - Cycles may fix the representative value
   - Cycles may create contradictions (return -1)

5. **Count Maximum Feasible Rods**
   - **If value fixed:** Count rods with value in range
   - **If value free:** Use sweep-line algorithm
     - For each rod j: find range of a_x where l_j ≤ a_j ≤ r_j
     - Find a_x value covering maximum rods

## Key Algorithms

### DFS (Constraint Propagation)
```cpp
DFS(node, linear_expression):
  For each neighbor of node:
    Compute neighbor's linear expression
    If neighbor visited, check consistency
    Else, recursively DFS neighbor
```

### Sweep Line (Interval Maximization)
```cpp
Create interval endpoints:
  For each rod: [start_point, +1] and [end_point+1, -1]
Sort endpoints
Sweep through, tracking active intervals
Find maximum active count
```

## Test Results

```
Test 1:  PASS (expected: -1, 2)
Test 2:  PASS (expected: 3)
Test 3:  PASS
Test 4:  PASS
Test 5:  PASS
Test 6:  PASS
Test 7:  PASS
Test 8:  PASS
Test 9:  PASS
Test 10: PASS
Test 11: PASS
Test 12: PASS
Test 13: PASS

All 13/13 tests PASS ✓
```

## Usage

Build and run commands (run from the `prob2_silver_season26contest1` folder):

```bash
# enter the problem folder
cd prob2_silver_season26contest1

# compile the solution
g++ -std=c++17 -O2 solution.cpp -o solution

# run a single test (example: test 1)
./solution < 1.in

# run all tests (1..13) and report pass/fail
for i in {1..13}; do
   ./solution < "$i.in" > out && diff -q out "$i.out" && echo "Test $i: PASS" || echo "Test $i: FAIL"
done

# optional: use the provided test harness (if executable)
if [ -x ./test ]; then
   ./test
fi
```

Notes:
- Input files are named `1.in`, `2.in`, ...; expected outputs are `1.out`, `2.out`, ...
- Ensure `solution` is executable (`chmod +x solution`) before running the loop.

If the test loop produces only `Test N: PASS` messages (or no failures), all tests matched their expected outputs.

## Complexity

- **Time:** O((N + M) log(N + M))
  - DFS traversal: O(N + M)
  - Sorting intervals: O(M log M)
- **Space:** O(N + M)

## Constraints

- 1 ≤ N ≤ 2×10⁵
- 1 ≤ M ≤ 4×10⁵ (across all test cases)
- -10⁹ ≤ values ≤ 10⁹
- Uses 64-bit integers to prevent overflow
