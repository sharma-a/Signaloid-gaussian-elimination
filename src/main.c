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

    FILE *fptr;
   if(!(fptr=fopen("mnt/Abmat","w"))) {printf ("\nFile Error.\n"); return -1;}
       

   for(int i=0;i<nRow;++i){
      for(int j=0;j<nCol;++j){
          double mu=uniformRandom(-10,10);
          double sigma=uniformRandom(.3,1.5);
          *at(&A,i,j)=libUncertainDoubleGaussDist(mu,sigma);
          *at(&B,i,j)=*at(&A,i,j);
           fprintf(fptr,"%.4f, %.4f\n",mu, sigma);
      }
   }


   fclose(fptr);

 

   double* soln=(double*) malloc(N*sizeof(double));

   //printMatrix(&A);

   solveEqnGaussJordan(&A,soln);


   //printf("After Gauss Jordan:\n");
   //printMatrix(&A);

   if(!(fptr=fopen("mnt/Absoln","w"))) {printf ("\nFile Error.\n"); return -1;}


   printf("Soln:\n");
   for(int i=0;i<N;++i){
       soln[i]=*at(&A,i,nCol-1)/(*at(&A,i,i));
       printf("%.4lf, %.4lf, %.4lf\n",soln[i],libUncertainDoubleNthMoment(soln[i],1), libUncertainDoubleNthMoment(soln[i],2));
       fprintf(fptr,"%.4lf, %.4lf, %.4lf\n",soln[i],libUncertainDoubleNthMoment(soln[i],1), libUncertainDoubleNthMoment(soln[i],2));
   }
   printf("\n");
   fclose(fptr);


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
