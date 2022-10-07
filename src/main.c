#include "matrix.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <uncertain.h>

int main(){

   Matrix A;
   int nRow, nCol;
   int N=3;
   nRow=N;
   nCol=N+1;
   initialiseMatrix(&A,nRow,nCol);
   *at(&A,0,0)=3.0f;
   *at(&A,0,1)=5.0f;
   *at(&A,0,2)=3.0f;
   *at(&A,1,0)=4.0f;
   *at(&A,1,1)=4.0f;
   *at(&A,1,2)=5.0f;
   *at(&A,2,1)=7.0f;
   *at(&A,2,2)=8.0f;
   {
    double sampleA20[]={2,2.5};
    *at(&A,2,0) = libUncertainDoubleDistFromSamples(sampleA20,sizeof(sampleA20)/sizeof(double));
   }
   *at(&A,0,3)=3.0f;
   *at(&A,1,3)=4.0f;
   *at(&A,2,3)=6.0f;
 

   

   double* soln=(double*) malloc(N*sizeof(double));

   printMatrix(&A);

  // solveEqn(&A,soln);
   gaussJordan(&A);
   printf("After Gauss Jordan:\n");
   printMatrix(&A);


   printf("Soln:\n");
   for(int i=0;i<N;++i)
       soln[i]=*at(&A,i,nCol-1)/(*at(&A,i,i));
       printf("%7.5lf  ",soln[i]);

   printf("\n");

   /*for(int ii=0;ii<4;++ii){
       solveTriangular(&A,soln);
       for(int i=0;i<N;++i)
           printf("%7.5lf  ",soln[i]);

       printf("\n");
   }*/


   freeMatrix(&A);
   free(soln);

   return 0;
   
}
