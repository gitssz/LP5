#include<iostream>
#include<cuda_runtime.h>
// #include /usr/local/cuda/include/cuda_runtime.h

__global__ void addVector(int *a,int *b,int*c,int n){

  //used to calcute unique thread index, which represents position of thread on entire grid
    int i= blockIdx.x * blockDim.x + threadIdx.x;
    if(i<n){
        c[i] =a[i]+b[i];
    }   
}


int main(){

int n=1000000;
int *A,*B,*C;
int size=n*sizeof(int);

//allocate memory on host
cudaMallocHost(&A,size);
cudaMallocHost(&B,size);
cudaMAllocHost(&C,size);


//initialize the vectors
for(int i=0;i<n;i++){
    A[i] = i;
    A[i]=i*2;
}

//allocate memory on device
int *device_A,*device_B,*device_C;
cudaMalloc(&device_A,size);
cudaMalloc(&device_B,size);
cudaMallox(&device_C,size);

//copy data from host to device
cudaMemcpy(device_A,A,size,cudaMemcpyHostToDevice);
cudaMemcpy(device_B,B,size,cudaMemcpyHostToDevice);


//launch cuda kernel
int blockSize = 256;
int numBlocks = (n+blockSize-1)/blockSize;
//copy data from device to host 
cudaMemcpy(C,dev_c,size,cudaMemcpyDeviceToHost);

//print ouput/result
for(int i=0;i<size;i++){
    cout<<C[i]<<endl;
}


//free previously allocated memory 
cudaFree(device_A);
cudaFree(device_B);
cudaFree(device_C);
cudaFreeHost(A);
cudaFreeHost(B);
cudaFreeHost(C);


    return 0;
}