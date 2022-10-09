#ifndef __MATRIX_H
#define __MATRIX_H

#define __ABS__(x) ((x)>0?(x):-(x))

typedef struct Matrix_{
    int nRow;
    int nCol;
    double* mat;
    int* indices; //stores the order in which the rows are arranged

} Matrix;

double* at(Matrix* m, int i, int j); 
//gives the pointer to the (0 indexed) ith row, jth column of matrix m
//all reading from and writing to matrices is done using these pointers

void initialiseMatrix(Matrix* m, int nRow, int nCol); 
//like a constructor for the Matrix struct. allocates memory, initialises indices.

void printMatrix(Matrix *m);

void swapRow(Matrix *m, int i, int j);

void addRowMultiple(Matrix *m, int to, int from, double mul);

void getColumnPointers(double** out,Matrix* m,int j);

void gaussTriangulise(Matrix *in);

void gaussJordan(Matrix *in);

double* solveEqn(Matrix *in);

double* solveEqnGaussJordan(Matrix *in);

void freeMatrix(Matrix *in);

Matrix* createCopyMatrix(Matrix *in);
//creates a new Matrix struct and copies contents of in into it. returns pointer to the new object.

Matrix* readFromFile(char* filename);

void printSoln(double* soln, int nRow);
#endif
