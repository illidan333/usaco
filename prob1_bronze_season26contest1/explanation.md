# Chip Exchange - Explanation

## Key idea
After any extra chips are added, Bessie can exchange all possible type B chips into type A. So the only thing that matters is the *maximum* type A count achievable after exchanges.

Let the extra chips be $n_A$ and $n_B$. The resulting A count is:

$$
A + n_A + \left\lfloor \frac{B + n_B}{c_B} \right\rfloor c_A
$$

We need the smallest $x = n_A + n_B$ that *guarantees* the result is at least $f_A$.

## Step 1: check if $x = 0$ works
If we convert all current B into A:

$$
A_{init} = A + \left\lfloor \frac{B}{c_B} \right\rfloor c_A
$$

If $A_{init} \ge f_A$, the answer is $0$.

## Step 2: find the largest failing total
If $A_{init} < f_A$, define:

$$
need = f_A - 1 - A_{init}
$$

This is how many more A chips we still need to *fail by exactly one*.

To maximize the failing total $y = n_A + n_B$, we should make $B + n_B$ end at remainder $c_B - 1$ (just before another exchange would give more A). That forces:

$$
n_{B,0} = c_B - 1 - (B \bmod c_B)
$$

Now we distribute the remaining $need$ as extra chips to maximize $n_A + n_B$:

- If $c_A \ge c_B$, then each extra chip is best spent as A, so add $need$.
- Otherwise, each group of $c_A$ A-chips can be swapped for $c_B$ B-chips to make $y$ larger.

That yields:

$$
\text{if } c_A \ge c_B: \quad y = n_{B,0} + need
$$

$$
\text{else}: \quad y = n_{B,0} + \left\lfloor \frac{need}{c_A} \right\rfloor c_B + (need \bmod c_A)
$$

The answer is $y + 1$.

## Algorithm
1. Compute $A_{init}$.
2. If $A_{init} \ge f_A$, return $0$.
3. Compute $need$ and $n_{B,0}$.
4. Compute $y$ using the cases above.
5. Return $y + 1$.

## Mermaid diagram
```mermaid
flowchart TD
    S[Read A,B,cA,cB,fA] --> C[Compute A_init = A + floor(B/cB)*cA]
    C --> D{A_init >= fA?}
    D -- Yes --> Z[Answer = 0]
    D -- No --> E[need = fA - 1 - A_init]
    E --> F[nB0 = cB - 1 - (B mod cB)]
    F --> G{cA >= cB?}
    G -- Yes --> H[y = nB0 + need]
    G -- No --> I[y = nB0 + floor(need/cA)*cB + (need mod cA)]
    H --> J[Answer = y + 1]
    I --> J
```

## Example
Input:
```
A=2 B=3 cA=1 cB=1 fA=6
```

- $A_{init} = 2 + \lfloor 3/1 \rfloor \cdot 1 = 5$ (not enough)
- $need = 6 - 1 - 5 = 0$
- $n_{B,0} = 1 - 1 - (3 \bmod 1) = 0$
- $c_A \ge c_B$, so $y = 0$
- Answer $= y + 1 = 1$

## Complexity
Each test case uses a constant number of arithmetic operations.

- Time: $O(1)$ per test case
- Memory: $O(1)$
