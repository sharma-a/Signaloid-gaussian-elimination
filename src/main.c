#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <uncertain.h>
#include "Matrix.h"

int readLineFromFile(char* str, char* type, double* ret){
    char *token;
    int nSamp=0;
    token=strtok(str,",");
    strcpy(type,token);
    token=strtok(NULL,",");
    while(token!=NULL){
        ret[nSamp++]=atof(token);
        token=strtok(NULL,","); 
    }
    return nSamp;
}



Matrix* readFromFile(char* filename){
    FILE *fptr;
    if(!(fptr=fopen(filename,"r"))) {printf ("\nFile Error.\n"); return NULL;}
    int nRow, nCol;
    fscanf(fptr,"%d\n",&nRow);
    nCol=nRow+1;
    double samples[30];
    int nSamp;
    char type[20];
    printf("nRow is %d\n",nRow);
    Matrix* ret;
    ret=(Matrix*) malloc(sizeof(Matrix));
    initialiseMatrix(ret,nRow,nCol);

    for(int i=0;i<nRow;++i){
        for(int j=0;j<nCol;++j){
            char line[300];
            char type[20];
            fgets(line, 300, fptr);
            nSamp=readLineFromFile(line, type, samples);
            if(strcmp(type,"gauss")==0){
                *at(ret,i,j=libUncertainDoubleGaussDist(samples[0],samples[1]);
            }
            else if(strcmp(type,"unif")==0){
                *at(ret,i,j=libUncertainDoubleUniformDist(samples[0],samples[1]);
            }
            else if(strcmp(type,"exp")==0){
                *at(ret,i,j=libUncertainDoubleExponentialDist(samples[0]);
            }
            else if(strcmp(type,"custom")==0){
                if(nSamp==1) *at(ret,i,j)=samples[0];
                else *at(ret,i,j)=libUncertainDoubleDistFromSamples(samples,nSamp);

            }
        }
    }

    fclose(fptr);
    return ret;
}


int main(){
    char* filename="mnt/Mixinput";
    Matrix *A=readFromFile(filename);
    printMatrix(A);
}
