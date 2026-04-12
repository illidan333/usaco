# Photoshoot - Explanation

## Key idea
Each update changes a single cell by some delta. A K x K square sum changes by that delta if and only if the square contains that cell. There are only up to K positions in each direction where a top-left corner could include the cell, so only O(K^2) squares change per update.

Since K <= 25, we can explicitly maintain the sum for every K x K square in an (N-K+1) x (N-K+1) array and update the affected squares each time. Track the maximum sum as we go.

## Update effect
For a cell (r, c), the top-left corner (i, j) must satisfy:

- i in [r - K + 1, r]
- j in [c - K + 1, c]
- and also 0 <= i, j <= N - K

We clamp these ranges to the valid bounds and add the delta to each square in the rectangle of top-left positions. Update the global maximum after each change.

## Algorithm
1. Keep grid[r][c] and square_sum[i][j] for all top-left corners.
2. For each update, compute delta = new_value - grid[r][c].
3. Update all square_sum in the valid top-left rectangle.
4. Track max_sum and output after each update.

## Correctness sketch
- Any K x K square contains (r, c) if its top-left corner is within the computed ranges, so every affected square sum increases by delta.
- Squares outside this rectangle do not contain the cell and remain unchanged.
- Therefore all square sums are correctly maintained after each update, and max_sum is the maximum attractiveness index.

## Complexity
Each update touches at most K^2 squares.

- Time: O(Q * K^2)
- Memory: O(N^2)
