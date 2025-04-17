# CSR for Sparse Matrices

A C++ project that demonstrates reading, converting, and storing matrices using the **Compressed Sparse Row (CSR)** format.

## Features
- Read dense matrix from `.txt` file
- Convert to **CSR format**
- Print & save matrix in CSR format
- Read matrix back from CSR
- Access value at A\[i\]\[j\] directly from CSR format

## Project Structure
```
crs-for-sparse-matrices/
├── data/
│   ├── matrix.txt              # Original dense matrix
│   ├── matrix_CSR.txt          # Matrix stored in CSR format
│   ├── write_matrix.txt        # Output: matrix as .txt
│   ├── write_CSR.txt           # Output: CSR matrix saved to .txt
│   └── write.txt               # Another CSR write output (same as above?)
├── main.cpp
└── README.md
```

## How to compile and run

Create the build directory if it doesn't exist
```
mkdir -p build
```
Compile
```
g++ -o build/csr_example main.cpp -Iinclude
```
Run
```
./build/csr_example
```

