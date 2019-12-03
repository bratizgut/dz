#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <float.h>

void matrixMul(float ***res, float **a, float **b, int N){
    for(size_t i = 0; i < N; i++){
        for(size_t j = 0; j < N; j++){
            for(size_t k = 0; k < N; k++){
                (*res)[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void matrixEq(float ***res, float **a, int N){
    for(size_t i = 0; i < N; i++){
        for(size_t j = 0; j < N; j++){
            (*res)[i][j] = a[i][j];
        }
    }
}

void matrixSum(float ***arr, float **arrb, int N){
    for(size_t i = 0; i < N; i++){
        for(size_t j = 0; j < N; j++){
            (*arr)[i][j] += arrb[i][j];
        }
    }
}

void matrixZero(float ***res, int N){
    for(size_t i = 0; i < N; i++){
        for(size_t j = 0; j < N; j++){
            (*res)[i][j] = 0;
        }
    }
}

int main(){

    int N = 10;
    int M = 1000000;
    srand(time(0));

    float **arr;
    arr = (float **)malloc(N * sizeof(float*));
    for(size_t i = 0; i < N; i++)
        arr[i] = (float *)malloc(N * sizeof(float));

    float **arrb;
    arrb = (float **)malloc(N * sizeof(float*));
    for(size_t i = 0; i < N; i++)
        arrb[i] = (float *)malloc(N * sizeof(float));

    float **res;
    res = (float **)malloc(N * sizeof(float*));
    for(size_t i = 0; i < N; i++)
        res[i] = (float *)malloc(N * sizeof(float));
    matrixZero(&res, N);

    float **Rn;
    Rn = (float **)malloc(N * sizeof(float*));
    for(size_t i = 0; i < N; i++)
        Rn[i] = (float *)malloc(N * sizeof(float));
    matrixZero(&Rn, N);

    float **start;
    start = (float **)malloc(N * sizeof(float*));
    for(size_t i = 0; i < N; i++)
        start[i] = (float *)malloc(N * sizeof(float));
    matrixZero(&start, N);

    float **buf;
    buf = (float **)malloc(N * sizeof(float*));
    for(size_t i = 0; i < N; i++)
        buf[i] = (float *)malloc(N * sizeof(float));
    matrixZero(&buf, N);

    for(size_t i = 0; i < N; i++){
        for(size_t j = 0; j < N; j++){
            arr[i][j] = (float)rand() / 10000;
            start[i][j] = arr[i][j];
            printf("%6.3f ", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    float A1 = -FLT_MAX, Ainf = -FLT_MAX;
    for(size_t i = 0; i < N; i++){
        float buffer = 0;
        for(size_t j = 0; j < N; j++){
            buffer += arr[i][j];
        }
        if (buffer > A1)
            A1 = buffer;
    }
    for(size_t i = 0; i < N; i++){
        float buffer = 0;
        for(size_t j = 0; j < N; j++){
            buffer += arr[j][i];
        }
        if (buffer > Ainf)
            Ainf = buffer;
    }
    
    for(size_t i = 0; i < N; i++){
        for(size_t j = 0; j < N; j++){
            arrb[i][j] = arr[j][i] / (A1 * Ainf);
        }
    }

    matrixMul(&buf, arrb, arr, N);
    matrixEq(&arr, buf, N);
    matrixZero(&buf, N);
    for(size_t i = 0; i < N; i++){
        arr[i][i]--;
    }

    for(size_t i = 0; i < N; i++){
        for(size_t j = 0; j < N; j++){
            arr[i][j] = -arr[i][j]; 
        }
    }

    for(size_t i = 0; i < N; i++){
        for(size_t j = 0; j < N; j++){
            if(i = j){
                Rn[i][j] = 1;
                res[i][j] = 1;
            } else {
                Rn[i][j] = 1;
                res[i][j] = 0;
            }
        }
    }
    

    for(size_t i = 2; i < M; i++){
        matrixMul(&buf, Rn, arr, N);
        matrixEq(&Rn, buf, N);
        matrixZero(&buf, N);
        matrixSum(&res, Rn, N);
    }
    matrixMul(&buf, res, arrb, N);
    matrixEq(&res, buf, N);
    matrixZero(&buf, N);
    matrixMul(&buf, res, start, N);

    for(size_t i = 0; i < N; i++){
        for(size_t j = 0; j < N; j++){
            printf("%6.3f ", buf[i][j]);
        }
        printf("\n");
    }

    for(size_t i = 0; i < N; i++)
       free(arr[i]);
    free(*arr);
    
    for(size_t i = 0; i < N; i++)
       free(arrb[i]);
    free(*arrb);

    for(size_t i = 0; i < N; i++)
       free(res[i]);
    free(*res);

    for(size_t i = 0; i < N; i++)
       free(Rn[i]);
    free(*Rn);

    for(size_t i = 0; i < N; i++)
       free(buf[i]);
    free(*buf);

    return 0;
}
