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
    for(int i=0;i<nRow;++i)
        printf("%lf\n",soln[i]);
    freeMatrix(A);
    free(soln);

}
