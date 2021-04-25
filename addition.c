%%cu
#include<stdio.h>
#include<stdlib.h>
__global__ void gpu_add(int* A,int* B, int* C , int M){
    int thread = threadIdx.x + blockIdx.x *blockDim.x;
    if(thread < M){
    C[thread] = A[thread] + B[thread];
    }
}
int main(){
    int *h_a , *h_b , *h_c;
    int m = 10;
    /* printf("Enter the size of 1D array required for random number initialization\n");
    scanf("%d",&m); */
    cudaMallocHost((void **)&h_a , sizeof(int)*m);
    cudaMallocHost((void **)&h_b , sizeof(int)*m);
    cudaMallocHost((void **)&h_c , sizeof(int)*m);

    for (int i =0 ; i<m ; i++){
        h_a[i] = rand() %100;
        h_b[i] = rand() %100;
    }
    printf("Input String 1: \n");
    for (int j =0; j < m ; j++){
        printf("%d ",h_a[j]);
    }

    printf("\nInput String 2: \n");
        for (int j =0; j < m ; j++){
        printf("%d ",h_b[j]);
    }
    int *a,*b,*c;
    cudaMalloc((void **)&a,sizeof(int)*m);
    cudaMalloc((void **)&b,sizeof(int)*m);
    cudaMalloc((void **)&c,sizeof(int)*m);
    cudaMemcpy(a,h_a,sizeof(int)*m,cudaMemcpyHostToDevice);
    cudaMemcpy(b,h_b,sizeof(int)*m,cudaMemcpyHostToDevice);
    gpu_add<<<ceil(m/256.0),256>>>(a,b,c,m);

    cudaMemcpy(h_c,c,sizeof(int)*m,cudaMemcpyDeviceToHost);
    printf("\nResult is: \n");
    for(int i=0;i<m;i++){
        printf("%d ",h_c[i]);
    }
}
