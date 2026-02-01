# USACO Silver Problem: Nuclear Reactor Rod Optimization

## 📋 Project Contents

This directory contains a **complete solution** for the nuclear reactor problem with:
- ✅ Working C++ implementation (passes all 13 tests)
- ✅ Test harness code
- ✅ Comprehensive documentation
- ✅ Algorithm diagrams and flowcharts
- ✅ Example walkthroughs

## 📁 File Guide

### Core Implementation
| File | Purpose |
|------|---------|
| [solution.cpp](solution.cpp) | Main solution - ready for submission |
| [test.cpp](test.cpp) | Test harness with embedded test cases |

### Documentation
| File | Purpose |
|------|---------|
| [README.md](README.md) | Problem statement, approach, compilation guide |
| [EXPLANATION.md](EXPLANATION.md) | Detailed algorithm with key insights |
| [ALGORITHM_DIAGRAMS.md](ALGORITHM_DIAGRAMS.md) | Mermaid flowcharts and state diagrams |
| [SOLUTION_SUMMARY.md](SOLUTION_SUMMARY.md) | Quick reference and complexity analysis |

### Test Data
| Files | Purpose |
|-------|---------|
| 1.in - 13.in | Input test cases |
| 1.out - 13.out | Expected outputs |

## 🚀 Quick Start

### Compile & Test
```bash
# Compile
g++ -o solution solution.cpp -std=c++17 -O2

# Run single test
./solution < 1.in

# Verify all tests
for i in {1..13}; do
  echo -n "Test $i: "
  ./solution < $i.in | diff -q - $i.out && echo "PASS" || echo "FAIL"
done
```

### Expected Output
```
Test 1: PASS
Test 2: PASS
...
Test 13: PASS
```

## 🎯 Problem Summary

**Goal:** Maximize power-generating rods in a nuclear reactor

**Constraints:**
- Each rod i has valid energy range [l_i, r_i]
- M equations of form: a_x + a_y = z
- Rod generates power only if l_i ≤ a_i ≤ r_i

**Solution:** Graph-based DFS with constraint propagation and sweep-line optimization

## 🔍 Algorithm Overview

1. **Model as Graph:** Constraints = edges between rods
2. **Process Connected Components:** Each component solved independently
3. **Express Linearly:** All rod energies = coef × representative_energy + constant
4. **Detect Cycles:** May fix variable values or reveal contradictions
5. **Optimize:** 
   - If variable fixed: count feasible rods
   - If variable free: use sweep-line for maximum coverage

## 📊 Key Metrics

- **Time Complexity:** O((N+M) log(N+M))
- **Space Complexity:** O(N+M)
- **Test Results:** 13/13 PASS ✓
- **Code Size:** ~100 lines (solution.cpp)

## 📚 Documentation Structure

```
Start Here
    ↓
README.md .......... Problem & Approach
    ↓
EXPLANATION.md ..... Algorithm Details
    ↓
ALGORITHM_DIAGRAMS.md .. Visual Flowcharts (Mermaid)
    ↓
SOLUTION_SUMMARY.md .... Implementation Notes
```

## 🧠 Understanding the Solution

### For Quick Understanding
1. Read [README.md](README.md) - Problem and high-level approach
2. Check Example Walkthrough section

### For Deep Understanding
1. Read [EXPLANATION.md](EXPLANATION.md) - Detailed algorithm
2. View [ALGORITHM_DIAGRAMS.md](ALGORITHM_DIAGRAMS.md) - Visual flowcharts
3. Study [solution.cpp](solution.cpp) - Implementation with comments

### For Learning
1. Try modifying [test.cpp](test.cpp) with custom test cases
2. Add debug output to track algorithm execution
3. Test edge cases: disconnected components, cycles, fixed values

## 🔧 Key Implementation Details

### Main Components

**1. Graph Construction**
```cpp
vector<vector<pair<int, ll>>> adj(n);
// For each constraint: connect rods with weight z
```

**2. DFS Traversal**
```cpp
// Express each rod as: a_j = coef * a_representative + constant
// Detect cycles and fixed values
```

**3. Interval Sweep-Line**
```cpp
// For free variable: find x value maximizing feasible rods
// Sort interval endpoints, track active intervals
```

## 🧪 Testing

### Run All Tests
```bash
./solution < [test_number].in
```

### Verify Against Expected
```bash
diff <(./solution < 1.in) 1.out
```

### Debug Output
Modify [solution.cpp](solution.cpp) to add:
```cpp
cerr << "Component " << i << ", fixed=" << has_set << endl;
cerr << "Answer: " << ans << endl;
```

## 📖 Example Test Case

**Input:**
```
3 2
10 -10 10
10 -10 10
1 2 0
2 3 0
```

**Solution:**
- Set a₁ = 10, a₂ = -10, a₃ = 10
- Check: a₁ + a₂ = 10 + (-10) = 0 ✓
- Check: a₂ + a₃ = (-10) + 10 = 0 ✓
- All rods within ranges → Answer: 3

## 🎓 Learning Outcomes

After studying this solution, you'll understand:
- ✓ Graph-based constraint propagation
- ✓ Connected component analysis
- ✓ Cycle detection in undirected graphs
- ✓ Sweep-line algorithm for interval problems
- ✓ Linear equation solving with integer constraints
- ✓ Handling edge cases (cycles, contradictions, fixed values)

## 📝 Notes

- Uses 64-bit integers (`long long`) to avoid overflow
- Handles both positive and negative rod energies
- Gracefully handles impossible cases (returns -1)
- Optimized for competitive programming (uses fast I/O)

## ✅ Verification Checklist

- [x] All 13 test cases pass
- [x] Code compiles without warnings
- [x] Handles edge cases
- [x] Correct complexity analysis
- [x] Clear, documented code
- [x] Comprehensive documentation

---

**Status:** ✅ Ready for submission

**Last Updated:** January 29, 2026
