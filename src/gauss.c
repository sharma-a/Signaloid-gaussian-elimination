#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>

#define __EPS__ 0.000001f

void gaussTriangulise(Matrix *in){
    int nRow=in->nRow;
    int nCol=in->nCol;
    int j, out, row, col;
    for(out=0;out<nRow-1;++out){
        //find the maximum element in the column for pivoting
        int maxIndex=out;
        double *maxPtr=at(in,maxIndex,out);
        for(j=out+1;j<nRow;++j){
            double* thisPtr=at(in,j,out);
            if(__ABS__(*thisPtr)>__ABS__(*maxPtr)) {maxIndex=j;maxPtr=thisPtr;}
        }
        swapRow(in,out,maxIndex);
        if(__ABS__(*maxPtr)<__EPS__) {printf("Singular Matrix\n. Exiting.\n"); exit(0);}

        for(row=out+1;row<nRow;++row){
            double alpha=*(at(in,row,out))/(*maxPtr);
            for(col=0;col<nCol;++col){
                if(col<=out) *at(in,row,col)=0.0f;
                else{
                    *at(in,row,col)-=*at(in,out,col)*alpha;
                } 
            }
        }
    }
}


double* solveEqn(Matrix *in){
    int nRow=in->nRow;
    int nCol=in->nCol;
    int i,j;
    if(nCol!=nRow+1) return NULL;
    double* soln=(double*) malloc(nRow*sizeof(double));
    gaussTriangulise(in);
    for(i=nRow-1;i>=0;--i){
        soln[i]=*at(in,i,nRow);
        for(j=nRow-1;j>i;--j){
            
            soln[i]-=*at(in,i,j)*soln[j];
        }
        soln[i]/=*at(in,i,i);
    }
    return soln;
}



void gaussJordan(Matrix *in){
    int nRow=in->nRow;
    int j, outerLoop, row, col;

    for(outerLoop=0;outerLoop<nRow;++outerLoop){
        int maxIndex=outerLoop;
        double *maxPtr=at(in,outerLoop,outerLoop);
        for(j=outerLoop+1;j<nRow;++j){
            double *thisPtr=at(in,j,outerLoop);
            if(__ABS__(*thisPtr)>__ABS__(*maxPtr)) {maxPtr=thisPtr; maxIndex=j;}
        }
        if(maxIndex!=outerLoop) swapRow(in,outerLoop,maxIndex);
        if(__ABS__(*maxPtr)<__EPS__) {printf("Singular Matrix\n. Exiting.\n"); exit(0);}

        for(row=0;row<nRow;row++){
            if(row==outerLoop) continue;
            double alpha=*at(in,row,outerLoop)/(*maxPtr);
            *at(in,row,outerLoop)=0.0f;
            for(col=outerLoop+1;col<nRow+1;++col){
                *at(in,row,col)-=alpha*(*at(in,outerLoop,col));
            }
        }
    }
}

double* solveEqnGaussJordan(Matrix *in){
    int nRow=in->nRow;
    int nCol=in->nCol;
    double* soln=(double*) malloc(nRow*sizeof(double));
    gaussJordan(in);
    for(int i=0;i<nRow;++i){
       soln[i]=*at(in,i,nCol-1)/(*at(in,i,i));
   }
   return soln;
} 
