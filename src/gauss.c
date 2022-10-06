#include "matrix.h"
#define __ABS__(x) ((x)>0?(x):-(x))

/*
void gaussTriangulise(Matrix *in){
    int nRow=in->nRow;
    int nCol=in->nCol;
    int j, out, row, col;
    for(out=0;out<nRow-1;++out){
        int maxIndex=out;
        double *maxPtr=at(in,maxIndex,out);
        for(j=out+1;j<nRow;++j){
            double* thisPtr=at(in,j,out);
            if(__ABS__(*thisPtr)>__ABS__(*maxPtr)) {maxIndex=j;maxPtr=thisPtr;}
        }
        swapRow(in,out,maxIndex);

        for(row=out+1;row<nRow;++row){
            double alpha=*(at(in,row,out))/(*maxPtr);
            for(col=0;col<nCol;++col){
                if(col<=out) *at(in,row,col)=0.0f;//remove this to take care of randomization.
                else{
                    *at(in,row,col)-=*at(in,out,col)*alpha;
                } 
            }
        }
    }
}


void solveEqn(Matrix *in, double* soln){
    int nRow=in->nRow;
    int nCol=in->nCol;
    int i,j;
    if(nCol!=nRow+1) return;
    gaussTriangulise(in);
    for(i=nRow-1;i>=0;--i){
        soln[i]=*at(in,i,nRow);
        for(j=nRow-1;j>i;--j){
            
            soln[i]-=*at(in,i,j)*soln[j];
        }
        soln[i]/=*at(in,i,i);
    }
}
*/



void gaussTriangulise(Matrix *in){
    int nRow=in->nRow;
    int nCol=in->nCol;
    int j, out, row, col;
    for(out=0;out<nRow-1;++out){
        int maxIndex=out;
        double *maxPtr=at(in,maxIndex,out);
        for(j=out+1;j<nRow;++j){
            double* thisPtr=at(in,j,out);
            if(__ABS__(*thisPtr)>__ABS__(*maxPtr)) {maxIndex=j;maxPtr=thisPtr;}
        }
        swapRow(in,out,maxIndex);

        for(row=out+1;row<nRow;++row){
            double alpha=*(at(in,row,out))/(*maxPtr);
            for(col=0;col<nCol;++col){
                *at(in,row,col)-=*at(in,out,col)*alpha;
            }
        }
    }
}


void solveTriangular(Matrix* in, double* soln){
    int nRow=in->nRow;
    int nCol=in->nCol;
    int i,j;
    for(i=nRow-1;i>=0;--i){
        soln[i]=*at(in,i,nRow);
        for(j=nRow-1;j>=0;--j){
            if(j==i) continue; 
            soln[i]-=*at(in,i,j)*soln[j];
        }
        soln[i]/=*at(in,i,i);
    }
}


void solveEqn(Matrix *in, double* soln){
    int nRow=in->nRow;
    int nCol=in->nCol;
    int i;
    if(nCol!=nRow+1) return;
    gaussTriangulise(in);
    for(i=0;i<nCol;++i) soln[i]=0.0f;
    solveTriangular(in, soln);
}



void gaussJordan(Matrix *in, Matrix *outm){
    int nRow=in->nRow;
    int nCol=in->nCol;
    int out, row, col;
    for(out=0;out<nRow;++out){
        double tmp=*at(in,out,out);
        for(col=0;col<nCol;++col){
            *at(in,out,col)/=tmp;
            *at(outm,out,col)/=tmp;
        }
        for(row=0;row<nRow;++row){
            if(row==out) continue;
            double alpha=*(at(in,row,out));
            for(col=0;col<nCol;++col){
                *at(in,row,col)-=*at(in,out,col)*alpha;
                *at(outm,row,col)-=*at(outm,out,col)*alpha;
            }
        }
    }
}
