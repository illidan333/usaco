# Solution Summary

...existing content...

## Usage

- Build the binary (example):
  g++ -std=c++17 -O2 prob2_silver_season26contest1/solution.cpp -o solution

- Run a single test (replace <testfile> with an actual input file, e.g. `1.in`):
  ./solution < 1.in
  or
  ./solution < <testfile>.in

- Run all numbered tests (example for tests 1..13):
  for i in {1..13}; do
    ./solution < "$i.in" | diff -q - "$i.out" || echo "Test $i failed"
  done

Note: The repository uses input files named like `1.in`, `2.in`, ... and expected outputs `1.out`, `2.out`, ...
Make sure the compiled binary `./solution` exists and is executable.

If the test loop prints nothing, that means all tests matched their expected outputs (no failures reported).
...existing content...
