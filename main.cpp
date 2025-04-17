// Read and store matrix in CSR format                  [X] Macro (READ_CSR)
// Print matrix in CSR format                           [X] Function
// Convert a matrix to CSR format                       [X] Macro (CONVERT_CSR)
// Save any matrix in CSR format to a .txt file         [X] Function
// Save any matrix to a .txt file                       [X] Function
// Identify A[i][j] in CSR format                       [X] Function

#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>

using namespace std;

// MACROS to use different functionalities (just write the macro in main)
#define READ_CSR    int* n = new int;                                   \
                    int* m = new int;                                   \
                    int* n_z;                                           \
                    double** AA;                                        \
                    int** JA;                                           \
                    read_CSR("data/matrix_CSR.txt", n, m, &n_z, &AA, &JA);   \
                    print_CSR(*n, *m, n_z, AA, JA);                     \
                    delete[] n_z;                                       \
                    for(int i = 0; i < *n; i++){                        \
                        delete[] AA[i];                                 \
                        delete[] JA[i];                                 \
                    }                                                   \
                    delete n;                                           \
                    delete m;

#define CONVERT_TO_CSR  int* n = new int;                                   \
                        int* m = new int;                                   \
                        double** A = read_matrix("data/matrix.txt", n, m);  \
                        print_matrix(A, n, m);                              \
                        write_matrix("data/write_matrix.txt", *n, *m, A);   \
                        cout << "\n\n";                                     \
                        int* n_z;                                           \
                        double** AA;                                        \
                        int** JA;                                           \
                        convert_to_CSR(*n, *m, A, &n_z, &AA, &JA);          \
                        print_CSR(*n, *m, n_z, AA, JA);                     \
                        write_CSR("data/write.txt", *n, *m, n_z, AA, JA);   \
                        for(int i = 0; i < *n; i++){                        \
                            delete[] A[i];                                  \
                            delete[] AA[i];                                 \
                            delete[] JA[i];                                 \
                        }                                                   \
                        delete[] n_z;                                       \
                        delete n;                                           \
                        delete m;

// Function declarations
void read_CSR(const char*, int*, int*, int**, double***, int***);
void print_CSR(int, int, int*, double**, int**);

void convert_to_CSR(int, int, double**, int**, double***, int***);
void write_CSR(const char*, int, int, int*, double**, int**);

double** read_matrix(const char*, int*, int*);
void write_matrix(const char*, int, int, double**);
void print_matrix(double**, int*, int*);

double get_value_from_CSR(int i, int j, int* n_z, double** AA, int** JA) {
    for(int k = 0; k < n_z[i]; k++) {
        if(JA[i][k] == j) {
            return AA[i][k];
        }
    }
    return 0.0; // Default for sparse matrices
}

// Function to read CSR format from file
void read_CSR(const char* filename, int* n, int* m, int** n_z, double*** AA, int*** JA){
    fstream fcin(filename);
    fcin >> *n;
    fcin >> *m;

    *n_z = new int[*n];
    *AA = new double*[*n];
    *JA = new int*[*n];

    for(int i = 0; i < *n; i++){
        fcin >> (*n_z)[i];
        (*JA)[i] = new int[(*n_z)[i]];
        (*AA)[i] = new double[(*n_z)[i]];

        for(int j = 0; j < (*n_z)[i]; j++){
            fcin >> (*JA)[i][j];
            fcin >> (*AA)[i][j];
        }
    }
    fcin.close();
}

// Function to print CSR format
void print_CSR(int n, int m, int* n_z, double** AA, int** JA){
    cout << n << ", " << m << "\n";

    for(int i = 0; i < n; i++){
        cout << n_z[i] << "\n";
        for(int j = 0; j < n_z[i]; j++){
            cout << JA[i][j] << " ";
            cout << AA[i][j] << " ";
        }
        cout << "\n";
    }
}

// Function to convert a standard matrix to CSR
void convert_to_CSR(int n, int m, double** A, int** n_z, double*** AA, int*** JA){
    *n_z = new int[n];
    *AA = new double*[n];
    *JA = new int*[n];

    int count = 0;

    for(int i = 0; i < n; i++){
        (*n_z)[i] = 0;
        for(int j = 0; j < m; j++){
            if(A[i][j] != 0){
                (*n_z)[i]++;
            }
        }

        (*AA)[i] = new double[(*n_z)[i]];
        (*JA)[i] = new int[(*n_z)[i]];

        count = 0;
        for(int j = 0; j < m; j++){
            if(A[i][j] != 0){
                (*AA)[i][count] = A[i][j];
                (*JA)[i][count] = j;
                count++;
            }
        }
    }
}

// Function to write CSR format to file
void write_CSR(const char* filename, int n, int m, int* n_z, double** AA, int** JA){
    ofstream fcout(filename);
    fcout << n << " " << m << "\n";

    for(int i = 0; i < n; i++){
        fcout << n_z[i] << "\n";
        for(int j = 0; j < n_z[i]; j++){
            fcout << JA[i][j] << " " << AA[i][j] << " ";
        }
        fcout << "\n";
    }

    fcout.close();
}

// Function to read a matrix from a file
double** read_matrix(const char* FileName, int* n, int* m){
    ifstream fcin(FileName);
    fcin >> *n;
    fcin >> *m;

    double** A = new double* [*n];
    for(int i = 0; i < *n; i++){
        A[i] = new double[*m];
        for(int j = 0; j < *m; j++){
            fcin >> A[i][j];
        }
    }

    return A;
}

// Function to write a matrix to a file
void write_matrix(const char* filename, int n, int m, double** A){
    ofstream fcout(filename);
    fcout << n << " " << m << "\n";
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            fcout << setw(7) << A[i][j] << " ";
        }
        fcout << "\n";
    }

    fcout.close();
}

// Function to print a matrix to console
void print_matrix(double** A, int* n, int* m){
    for(int i = 0; i < *n; i++){
        cout << "\n";
        for(int j = 0; j < *m; j++){
            cout << setw(10) << A[i][j] << " ";
        }
    }
}

int main(){
    CONVERT_TO_CSR;
    return 0;
}