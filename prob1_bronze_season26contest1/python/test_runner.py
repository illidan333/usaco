import os
import sys

from solution import solve_case


def run_file(path):
    with open(path, "r", encoding="utf-8") as f:
        data = f.read().strip().split()
    if not data:
        return []
    t = int(data[0])
    idx = 1
    results = []
    for _ in range(t):
        a = int(data[idx])
        b = int(data[idx + 1])
        c_a = int(data[idx + 2])
        c_b = int(data[idx + 3])
        f_a = int(data[idx + 4])
        idx += 5
        results.append(str(solve_case(a, b, c_a, c_b, f_a)))
    return results


def main():
    base_dir = os.path.dirname(os.path.abspath(__file__))
    test_dir = os.path.abspath(os.path.join(base_dir, "..", "testData"))
    if not os.path.isdir(test_dir):
        print("testData folder not found:", test_dir)
        return

    files = [f for f in os.listdir(test_dir) if f.endswith(".in")]
    files.sort(key=lambda x: (len(x), x))

    for name in files:
        path = os.path.join(test_dir, name)
        outputs = run_file(path)
        print(f"{name}:")
        print("\n".join(outputs))
        print("-")


if __name__ == "__main__":
    main()
