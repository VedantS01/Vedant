/***
 * 
 * Matrix Multplication 
 * 
 * Version               --     1.0
 * Author                --     Vedant Ashish Saboo (CS19B074)
 * 
 ***/

typedef unsigned short word;
#define MAX 1024

void MatMult(word A[][MAX], word B[][MAX], word C[][MAX]) {
    word i, j, k;
    for(i=0;i<MAX;i++) {
        for(j=0;j<MAX;j++) {
            C[i][j] = 0;
            for(k=0;k<MAX;k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void MatMultT(word A[][MAX], word B[][MAX], word C[][MAX]) {
    word i, j, k;
    for(i=0;i<MAX;i++) {
        for(j=0;j<MAX;j++) {
            C[i][j] = 0;
            for(k=0;k<MAX;k++) {
                C[i][j] += A[i][k] * B[j][k];
            }
        }
    }
}
