#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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
    char *sampA="111.132, 114.32, 110.98, 122.3, 116.75,113.55,117.11";
    int nSamp;
    double samples[50];

    nSamp=strToDoubleArray(sampA, samples);

    for(int i=0;i<nSamp;++i)
        printf("%lf\n",samples[i]);
 
    return 0;
}
