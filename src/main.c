#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <uncertain.h>
#include "matrix.h"


int main(){
    char* filename="mnt/Mixinput";
    Matrix *A=readFromFile(filename);
    int nRow=A->nRow;
    printMatrix(A);
    double* soln=solveEqn(A);
    printSoln(soln,nRow);

    freeMatrix(A);
    free(soln);

}
