#include "matrix.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <uncertain.h>
#include <math.h>



int main(int argc, char *argv[]){
    int N;
    Matrix A,B;
    int nRow, nCol;
    FILE *fptr;
    if(!(fptr=fopen("mnt/Abinp","r"))) {printf ("\nFile Error.\n"); return -1;}
    fscanf(fptr,"%d\n",&N);
    nRow=N;
    nCol=N+1;
    initialiseMatrix(&A,nRow,nCol);
    initialiseMatrix(&B,nRow,nCol);
    for(int i=0;i<nRow;++i){
      for(int j=0;j<nCol;++j){
          double mu;
          double sigma;
          fscanf(fptr,"%lf,%lf\n",&mu,&sigma);
          *at(&A,i,j)=libUncertainDoubleGaussDist(mu,sigma);
          *at(&B,i,j)=*at(&A,i,j);
      }
    }
    fclose(fptr);


    printMatrix(&A);
    double* soln=(double*) malloc(N*sizeof(double));
    solveEqnGaussJordan(&A,soln);



    if(!(fptr=fopen("mnt/Absoln","w"))) {printf ("\nFile Error.\n"); return -1;}
    printf("Soln:\n");
    for(int i=0;i<N;++i){
       printf("%.4lf, %.4lf, %.4lf\n",soln[i],libUncertainDoubleNthMoment(soln[i],1), libUncertainDoubleNthMoment(soln[i],2));
       fprintf(fptr,"%.4lf, %.4lf, %.4lf\n",soln[i],libUncertainDoubleNthMoment(soln[i],1), libUncertainDoubleNthMoment(soln[i],2));
    }
    printf("\n");
    fclose(fptr);


    double* solnB=(double*) malloc(N*sizeof(double));
    solveEqn(&B,solnB);
    printf("Soln Triangulise:\n");
    for(int i=0;i<N;++i){
       printf("%.4lf, %.4lf, %.4lf\n",solnB[i],libUncertainDoubleNthMoment(solnB[i],1), libUncertainDoubleNthMoment(solnB[i],2));
    }
    printf("\n");

    freeMatrix(&B);
    free(solnB);
    freeMatrix(&A);
    free(soln);

    return 0;

}
