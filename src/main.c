#include "matrix.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <uncertain.h>

int strToDoubleArray(char* str, double* ret){
    char *token;
    int nSamp=0;
    token=strtok(str,",");
    while(token!=NULL){
        ret[nSamp++]=atof(token);
        token=strtok(NULL,","); 
    }
    return nSamp;
}



int main(){

    FILE* fptr;
    fptr=fopen("Abinp","r");
    int nRow, nCol;
    fscanf(fptr,"%d\n",&nRow);
    nCol=nRow+1;
    char line[300];
    double samples[30];

    int nSamp;
    size_t len;

    Matrix A;
    initialiseMatrix(&A, nRow, nCol);
    for(int i=0;i<nRow;++i){
        for(int j=0;j<nCol;++j){
            //getline(&line, &len, fptr);
            fgets(line, 300, fptr);
            nSamp=strToDoubleArray(line, samples);
            *at(&A,i,j)=libUncertainDoubleDistFromSamples(samples,nSamp);
        }
    }

    fclose(fptr);


   double* soln=(double*) malloc(nRow*sizeof(double));

   printMatrix(&A);

   solveEqn(&A, soln);
    for(int i=0;i<nRow;++i){
       printf("%.4lf, %.4lf, %.4lf\n",soln[i],libUncertainDoubleNthMoment(soln[i],1), libUncertainDoubleNthMoment(soln[i],2));
       fprintf(fptr,"%.4lf, %.4lf, %.4lf\n",soln[i],libUncertainDoubleNthMoment(soln[i],1), libUncertainDoubleNthMoment(soln[i],2));
    }
 
   printf("\n");


   freeMatrix(&A);
   free(soln);

   return 0;
   
}
