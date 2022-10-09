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
    FILE *fptr;
    if(!(fptr=fopen("mnt/Abinp","r"))) {printf ("\nFile Error.\n"); return -1;}
    return -1;
    int nRow, nCol;
    fscanf(fptr,"%d\n",&nRow);
    nCol=nRow+1;
    char line[300];
    double samples[30];

    int nSamp;

    Matrix A;
    initialiseMatrix(&A, nRow, nCol);
    printf("here\n");
    for(int i=0;i<nRow;++i){
        for(int j=0;j<nCol;++j){
            //getline(&line, &len, fptr);
            fgets(line, 300, fptr);
            nSamp=strToDoubleArray(line, samples);
             for(int k=0;k<nSamp;++k)
                printf("%lf\t",samples[k]);
            printf("\n");
 //           *at(&A,i,j)=libUncertainDoubleDistFromSamples(samples,nSamp);
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
