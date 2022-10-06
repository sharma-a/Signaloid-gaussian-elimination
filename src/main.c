#include "matrix.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


double uniformRandom(double min, double max){
    return min+(max-min)*((double)random()/RAND_MAX);
}

int main(){
   srandom(34);

   Matrix A;
   int i,j,nRow, nCol;
   int N=5;
   nRow=N;
   nCol=N+1;
   initialiseMatrix(&A,nRow,nCol);
   for(i=0;i<nRow;++i){
       for(j=0;j<nCol;++j){
           *at(&A,i,j)=uniformRandom(-15,50.6);
       }
   }


   double* soln=(double*) malloc(N*sizeof(double));

   printMatrix(&A);

   solveEqn(&A,soln);
   printf("\n");
   for(int i=0;i<N;++i)
       printf("%7.5lf  ",soln[i]);

   printf("\n");


   freeMatrix(&A);
   free(soln);

   return 0;
   
}
