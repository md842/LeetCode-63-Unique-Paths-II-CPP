# LeetCode #63: Unique Paths II (Daily Challenge 08/12/2023)
This repository contains a C++ solution to the LeetCode daily challenge #63 for 08/12/2023. https://leetcode.com/problems/unique-paths-ii/

This solution beats 63.54% of users in runtime (3 ms) and 6.12% of users in memory usage (8.01 MB). 

## Running
Navigate to the directory containing the extracted implementation, then simply run `make` with the included Makefile.
```
cd LeetCode-63-Unique-Paths-II-CPP
make
```

The exact commands run by `make` are as follows:

```
g++ -Wall -O0 -pipe -fno-plt -fPIC unique_paths.cpp -o unique_paths
```

There are no arguments; the test cases are hard-coded into the C++ file.

## Cleaning up
Navigate to the directory containing the extracted implementation, then simply run `make clean` with the included Makefile.

```
cd LeetCode-63-Unique-Paths-II-CPP
make clean
```

The exact commands run by make clean are as follows:

```
rm -f unique_paths
```