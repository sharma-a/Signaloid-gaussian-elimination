#include "matrix.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <uncertain.h>




double uniformRandom(double min, double max){
    return min+(max-min)*((double)random()/RAND_MAX);
}


int main(int argc, char *argv[]){
    int N=atoi(argv[1]);

   srandom(time(NULL));
   Matrix A,B;
   int nRow, nCol;
   nRow=N;
   nCol=N+1;
   initialiseMatrix(&A,nRow,nCol);
   initialiseMatrix(&B,nRow,nCol);
       

   for(int i=0;i<nRow;++i){
      for(int j=0;j<nCol;++j){
          double mu=uniformRandom(-10,10);
          double sigma=uniformRandom(.3,1.5);
          *at(&A,i,j)=libUncertainDoubleGaussDist(mu,sigma);
          *at(&B,i,j)=*at(&A,i,j);
      }
   }



 

   double* soln=(double*) malloc(N*sizeof(double));

   //printMatrix(&A);

   clock_t beg,end;
   double tm;

   beg=clock();
   solveEqnGaussJordan(&A,soln);

   end=clock();

   tm=(double)(end-beg)/CLOCKS_PER_SEC;
   //printf("After Gauss Jordan:\n");
   //printMatrix(&A);


   printf("Soln:\n");
   for(int i=0;i<N;++i){
       soln[i]=*at(&A,i,nCol-1)/(*at(&A,i,i));
       printf("%7.5lf  ",soln[i]);
   }
   printf("\n");

   printf("Time taken:%lf\n",tm);


   double* solnB=(double*) malloc(N*sizeof(double));

   beg=clock();
   solveEqn(&B,solnB);
   end=clock();
   tm=(double)(end-beg)/CLOCKS_PER_SEC;

   

   printf("Soln Triangulise:\n");
   for(int i=0;i<N;++i){
       printf("%7.5lf  ",solnB[i]);
   }
   printf("\n");

   printf("Time taken:%lf\n",tm);



   freeMatrix(&B);
   free(solnB);


   freeMatrix(&A);
   free(soln);

   return 0;
   
}
