import sys


def solve_case(a, b, c_a, c_b, f_a):
    # Maximum A achievable without extra chips.
    initial_a = (b // c_b) * c_a + a
    if initial_a >= f_a:
        return 0

    # We want the largest invalid total (x-1), then add 1.
    need_a = f_a - 1 - initial_a

    # Choose n_B to make (B + n_B) divisible by c_B with remainder c_B-1.
    y = c_b - 1 - (b % c_b)

    if c_a >= c_b:
        y += need_a
    else:
        y += (need_a // c_a) * c_b + (need_a % c_a)

    return y + 1


def main():
    data = sys.stdin.read().strip().split()
    if not data:
        return
    t = int(data[0])
    idx = 1
    out_lines = []
    for _ in range(t):
        a = int(data[idx])
        b = int(data[idx + 1])
        c_a = int(data[idx + 2])
        c_b = int(data[idx + 3])
        f_a = int(data[idx + 4])
        idx += 5
        out_lines.append(str(solve_case(a, b, c_a, c_b, f_a)))
    sys.stdout.write("\n".join(out_lines))


if __name__ == "__main__":
    main()
