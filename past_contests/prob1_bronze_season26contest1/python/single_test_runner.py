import sys
from pathlib import Path

import solution


def parse_single_case(tokens):
    if len(tokens) == 5:
        return [int(x) for x in tokens]
    if len(tokens) >= 6:
        t = int(tokens[0])
        if t <= 0:
            raise ValueError("T must be positive when provided")
        if len(tokens) < 6:
            raise ValueError("Not enough values after T")
        return [int(x) for x in tokens[1:6]]
    raise ValueError("Expected 5 numbers or T followed by 5 numbers")


def main():
    default_path = Path(__file__).with_name("single_test_input.txt")
    path = Path(sys.argv[1]) if len(sys.argv) >= 2 else default_path
    if not path.is_file():
        print("Input file not found:", path)
        if path == default_path:
            print("Create it and paste numbers like: 2 3 1 1 6")
        return

    tokens = path.read_text(encoding="utf-8").strip().split()
    if not tokens:
        print("Input file is empty:", path)
        return

    a, b, c_a, c_b, f_a = parse_single_case(tokens)
    print(solution.solve(a, b, c_a, c_b, f_a))


if __name__ == "__main__":
    main()
