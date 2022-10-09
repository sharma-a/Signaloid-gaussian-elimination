#ifndef __MATRIX_H
#define __MATRIX_H

#define __ABS__(x) ((x)>0?(x):-(x))

typedef struct Matrix_{
    int nRow;
    int nCol;
    double* mat;
    int* indices;

} Matrix;

double* at(Matrix* m, int i, int j);

void initialiseMatrix(Matrix* m, int nRow, int nCol);

void printMatrix(Matrix *m);

void swapRow(Matrix *m, int i, int j);

void addRowMultiple(Matrix *m, int to, int from, double mul);

void getColumnPointers(double** out,Matrix* m,int j);

void gaussTriangulise(Matrix *in);

void gaussJordan(Matrix *in);

double* solveEqn(Matrix *in);

void solveEqnGaussJordan(Matrix *in, double* soln);

void solveTriangular(Matrix* in, double* soln);

void freeMatrix(Matrix *in);

Matrix* createCopyMatrix(Matrix *in);

Matrix* readFromFile(char* filename);


void printSoln(double* soln);
#endif
