import sys
from pathlib import Path

import solution


def main():
    default_path = Path(__file__).with_name("single_test_input.txt")
    path = Path(sys.argv[1]) if len(sys.argv) >= 2 else default_path
    if not path.is_file():
        print("Input file not found:", path)
        if path == default_path:
            print("Create it and paste input like: 4 2 3 2 2 11 3 4 3 3 1 100")
        return

    tokens = path.read_text(encoding="utf-8").strip().split()
    if not tokens:
        print("Input file is empty:", path)
        return

    if len(tokens) < 5:
        print("Input file does not contain enough values:", path)
        return

    n = int(tokens[0])
    k = int(tokens[1])
    if len(tokens) >= 3:
        q = int(tokens[2])
        if len(tokens) == 3 + q * 3:
            idx = 3
            updates = []
            for _ in range(q):
                r = int(tokens[idx]) - 1
                c = int(tokens[idx + 1]) - 1
                v = int(tokens[idx + 2])
                idx += 3
                updates.append((r, c, v))
        elif (len(tokens) - 2) % 3 == 0:
            updates = []
            idx = 2
            while idx + 2 < len(tokens):
                r = int(tokens[idx]) - 1
                c = int(tokens[idx + 1]) - 1
                v = int(tokens[idx + 2])
                idx += 3
                updates.append((r, c, v))
        else:
            print("Input does not match expected format (N K Q followed by Q updates).")
            return
    else:
        updates = []

    for value in solution.solve_all(n, k, updates):
        print(value)


if __name__ == "__main__":
    main()
