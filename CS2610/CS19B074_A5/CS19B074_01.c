/***
 * 
 * Performance Analysis for matrix multiplication 
 * 
 * Version               --     1.0
 * Author                --     Vedant Ashish Saboo (CS19B074)
 * 
 ***/
#include "CS19B074_03.c"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
typedef unsigned short word;
#define MAX 1024

int main() {
    word A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    word i, j;
    double time1, time2;
    struct timeval tp;
    struct timezone tz;
    for(i = 0; i < MAX; i++) {
        for(j = 0; j < MAX; j++) {
            A[i][j] = (word) (rand()%11) ;
        }
    }
    for(i = 0; i < MAX; i++) {
        for(j = 0; j < MAX; j++) {
            B[i][j] = (word) (rand()%11) ;
        }
    }

    gettimeofday(&tp,&tz);
    time1 = (double)tp.tv_sec + (double)tp.tv_usec / 1000000 ;
    MatMult(A,B,C);
    gettimeofday(&tp,&tz);
    time2 = (double)tp.tv_sec + (double)tp.tv_usec / 1000000 ;
    printf("\n TIME ELAPSED = %lf seconds\n", time2 - time1);
/*
    gettimeofday(&tp,&tz);
    time1 = (double)tp.tv_sec + (double)tp.tv_usec / 1000000 ;
    MatMultT(A,B,C);
    gettimeofday(&tp,&tz);
    time2 = (double)tp.tv_sec + (double)tp.tv_usec / 1000000 ;
    printf("\n TIME ELAPSED = %lf seconds\n", time2 - time1);
*/
    return 0;

}
