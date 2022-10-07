#ifndef __MATRIX_H
#define __MATRIX_H


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

void solveEqn(Matrix *in, double* soln);

void solveTriangular(Matrix* in, double* soln);

void freeMatrix(Matrix *in);


#endif
