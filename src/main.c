#include "matrix.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <uncertain.h>




double uniformRandom(double min, double max){
    return min+(max-min)*((double)random()/RAND_MAX);
}


int main(){

   srandom(time(NULL));
   Matrix A,B;
   int nRow, nCol;
   int N=10;
   nRow=N;
   nCol=N+1;
   initialiseMatrix(&A,nRow,nCol);
   initialiseMatrix(&B,nRow,nCol);
   {
       
      /* double sampleA00[]={3.2,2.8,3.3};
       double sampleA01[]={13.8,10.5,12.3};
       double sampleA02[]={5.3,5.8,5.0};
       double sampleA10[]={-3,-3.8,-3.5};
       double sampleA11[]={23.2,22.8,23.3};
       double sampleA12[]={7.2,7.8,8.1};
       double sampleA20[]={10.2,12.8,10.6};
       double sampleA21[]={0.8,1.2,0.8};
       double sampleA22[]={-3.2,-2.8,-3.3};
       double sampleb0[]={43.2,40.2,46.3};
       double sampleb1[]={23.2,22.8,23.3};
       double sampleb2[]={-13.2,-12.8,-15.0};
       *at(&A,0,0) = libUncertainDoubleDistFromSamples(sampleA00,sizeof(sampleA00)/sizeof(double));
       *at(&A,0,1) = libUncertainDoubleDistFromSamples(sampleA01,sizeof(sampleA01)/sizeof(double));
       *at(&A,0,2) = libUncertainDoubleDistFromSamples(sampleA02,sizeof(sampleA02)/sizeof(double));
       *at(&A,1,0) = libUncertainDoubleDistFromSamples(sampleA10,sizeof(sampleA10)/sizeof(double));
       *at(&A,1,1) = libUncertainDoubleDistFromSamples(sampleA11,sizeof(sampleA11)/sizeof(double));
       *at(&A,1,2) = libUncertainDoubleDistFromSamples(sampleA12,sizeof(sampleA12)/sizeof(double));
       *at(&A,2,0) = libUncertainDoubleDistFromSamples(sampleA20,sizeof(sampleA20)/sizeof(double));
       *at(&A,2,1) = libUncertainDoubleDistFromSamples(sampleA21,sizeof(sampleA21)/sizeof(double));
       *at(&A,2,2) = libUncertainDoubleDistFromSamples(sampleA22,sizeof(sampleA22)/sizeof(double));

       *at(&A,0,3) = libUncertainDoubleDistFromSamples(sampleb0,sizeof(sampleb0)/sizeof(double));
       *at(&A,1,3) = libUncertainDoubleDistFromSamples(sampleb1,sizeof(sampleb1)/sizeof(double));
       *at(&A,2,3) = libUncertainDoubleDistFromSamples(sampleb2,sizeof(sampleb2)/sizeof(double));*/
   }


   for(int i=0;i<nRow;++i){
      for(int j=0;j<nCol;++j){
          double mu=uniformRandom(-10,10);
          double sigma=uniformRandom(.3,1.5);
          *at(&A,i,j)=libUncertainDoubleGaussDist(mu,sigma);
         *at(&B,i,j)=*at(&A,i,j);
      }
   }



 

   double* soln=(double*) malloc(N*sizeof(double));

   printMatrix(&A);

   solveEqnGaussJordan(&A,soln);

   printf("After Gauss Jordan:\n");
   printMatrix(&A);


   printf("Soln:\n");
   for(int i=0;i<N;++i){
       soln[i]=*at(&A,i,nCol-1)/(*at(&A,i,i));
       printf("%7.5lf  ",soln[i]);
   }
   printf("\n");



   double* solnB=(double*) malloc(N*sizeof(double));
   solveEqn(&B,solnB);


   printf("Soln Triangulise:\n");
   for(int i=0;i<N;++i){
       printf("%7.5lf  ",solnB[i]);
   }
   printf("\n");




   freeMatrix(&B);
   free(solnB);


   freeMatrix(&A);
   free(soln);

   return 0;
   
}
