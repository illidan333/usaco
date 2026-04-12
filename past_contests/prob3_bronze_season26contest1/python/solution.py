def solve_all(n, k, updates):
    size = n - k + 1
    square_sum = [[0] * size for _ in range(size)]
    grid = [[0] * n for _ in range(n)]

    max_sum = 0
    outputs = []

    for r, c, v in updates:
        delta = v - grid[r][c]
        grid[r][c] = v

        r_start = max(0, r - k + 1)
        r_end = min(r, n - k)
        c_start = max(0, c - k + 1)
        c_end = min(c, n - k)

        for i in range(r_start, r_end + 1):
            row = square_sum[i]
            for j in range(c_start, c_end + 1):
                new_sum = row[j] + delta
                row[j] = new_sum
                if new_sum > max_sum:
                    max_sum = new_sum

        outputs.append(max_sum)

    return outputs


def main():
    first = input().split()
    if not first:
        return
    n, k = map(int, first)
    q = int(input())
    updates = []
    for _ in range(q):
        r, c, v = map(int, input().split())
        updates.append((r - 1, c - 1, v))

    for value in solve_all(n, k, updates):
        print(value)


if __name__ == "__main__":
    main()
