#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

/*
Function implementations of the operations on my custom matrix data structure.
The names of functions are self-explanatory. The header "matrix.h" has some more comments.
The Matrix is always passed through a pointer to these functions
*/



double* at(Matrix* m, int i, int j){
    return m->mat+m->nCol*(m->indices[i])+j;
}


void printMatrix(Matrix *m){
    int i,j;
    printf("\n");
    for(i=0;i<m->nRow;++i){
        for(j=0;j<m->nCol;++j){
            printf("%12.5lf   ",*at(m,i,j));
        }
        printf("\n");
    }
}

void initialiseMatrix(Matrix* m, int nRow, int nCol){
    int i;
    m->nRow=nRow;
    m->nCol=nCol;
    m->mat=(double*) malloc(nRow * nCol* sizeof(double));
    m->indices=(int*) malloc(nRow * sizeof(int));
    for(i=0;i<nRow;i++){
        m->indices[i]=i;
    }
}


Matrix* createCopyMatrix(Matrix *in){
    Matrix* ret;
    ret=(Matrix*) malloc(sizeof(Matrix));
    initialiseMatrix(ret, in->nRow, in->nCol);
    for(int i=0;i<in->nRow;++i){
        for(int j=0;j<in->nCol;++j){
            *at(ret,i,j)=*at(in,i,j);
        }
    }
    return ret;
}


void swapRow(Matrix* m, int i, int j){
    int tmp=m->indices[j];
    m->indices[j]=m->indices[i];
    m->indices[i]=tmp;
}

void addRowMultiple(Matrix* m, int to, int from, double mul){
   int nCol=m->nCol;
   int j;
   for(j=0;j<nCol;++j){
       *at(m,to,j)+=*at(m,from,j)*mul;
   }
}

void getColumnPointers(double** out,Matrix* m,int j){
    int i;
    for(i=0;i<m->nRow;++i)
        out[i]=m->mat+m->nCol*(m->indices[i])+j;
}

void freeMatrix(Matrix *in){
    free(in->mat);
    free(in->indices);
}
