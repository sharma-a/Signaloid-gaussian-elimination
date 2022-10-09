#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <uncertain.h>
#include "matrix.h"


int main(int argc, char* argv[]){
    char* filename=argv[1];
    Matrix *A=readFromFile(filename);
    Matrix *Acopy=createCopyMatrix(A);

    int nRow=A->nRow;

    printf("Gauss Triangulization\n");   
    double* soln=solveEqn(A);
    printSoln(soln,nRow);



    printf("Gauss Jordan\n");   
    double* solnGJ=solveEqnGaussJordan(Acopy);
    printSoln(solnGJ,nRow);

    freeMatrix(A);
    freeMatrix(Acopy);
    free(soln);

}
