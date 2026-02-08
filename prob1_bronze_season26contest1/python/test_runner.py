import os
import time

import solution


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
        results.append(str(solution.solve(a, b, c_a, c_b, f_a)))
    return results


def read_expected(path):
    with open(path, "r", encoding="utf-8") as f:
        content = f.read().strip()
    if not content:
        return []
    return content.split()


def main():
    base_dir = os.path.dirname(os.path.abspath(__file__))
    test_dir = os.path.abspath(os.path.join(base_dir, "..", "testData"))
    if not os.path.isdir(test_dir):
        print("testData folder not found:", test_dir)
        return

    files = [f for f in os.listdir(test_dir) if f.endswith(".in")]
    files.sort(key=lambda x: (len(x), x))

    total_start = time.perf_counter()
    for name in files:
        in_path = os.path.join(test_dir, name)
        out_name = name.replace(".in", ".out")
        out_path = os.path.join(test_dir, out_name)

        case_start = time.perf_counter()
        outputs = run_file(in_path)
        expected = read_expected(out_path) if os.path.exists(out_path) else None

        if expected is None:
            status = "MISSING .out"
        elif outputs == expected:
            status = "PASS"
        else:
            status = "FAIL"

        elapsed_ms = (time.perf_counter() - case_start) * 1000.0
        print(f"{name}: {status} ({elapsed_ms:.2f} ms)")

    total_ms = (time.perf_counter() - total_start) * 1000.0
    print(f"Total: {total_ms:.2f} ms")


if __name__ == "__main__":
    main()
