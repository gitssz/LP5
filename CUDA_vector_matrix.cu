#include<iostream>
#include<cuda_runtime.h>
// #include /usr/local/cuda/include/cuda_runtime.h

//add vector kernel
__global__ void addVector(int *a,int *b,int*c,int n){

  //used to calcute unique thread index, which represents position of thread on entire grid
    int i= blockIdx.x * blockDim.x + threadIdx.x;
    if(i<n){
        c[i] =a[i]+b[i];
    }   
}

//matrix multiplication kernel
__global__ void matrixMultiplication(int *a,int *b, int *c , int size){

    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if(row<size && col<<size){
        int product_sum=0;
        for(int k=0;k<size;k++){
            product_value += A[row*size + k] * B[k*size +col]
        }
        c[row*n+col] = product_value[];
    }
}

//utility functions
void initializeVector(int* vector, int size) {
    for (int i = 0; i < size; i++) {
        vector[i] = rand() % 10;
    }
}

void initializeMatrix(int* matrix, int size) {
    for (int i = 0; i < size * size; i++) {
        matrix[i] = rand() % 10;
    }
}

void printVector(int* vector, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", vector[i]);
    }
    printf("\n");
}

void printMatrix(int* matrix, int size) {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            printf("%d ", matrix[row * size + col]);
        }
        printf("\n");
    }
    printf("\n");
}



int main(){

int n=4;

//===============vector addition=================

int *A,*B,*C;
int size=n*sizeof(int);

//allocate memory on host
cudaMallocHost(&A,size);
cudaMallocHost(&B,size);
cudaMAllocHost(&C,size);

//initialize the vectors
initializeVector(A,n);
initializeVector(B,n);

printf("Vector A: \n");
printVector(A, size);
printf("Vector B: \n");
printVector(B, size);

//allocate memory on device
int *device_A,*device_B,*device_C;
cudaMalloc(&device_A,size);
cudaMalloc(&device_B,size);
cudaMalloc(&device_C,size);

//copy data from host to device
cudaMemcpy(device_A,A,size,cudaMemcpyHostToDevice);
cudaMemcpy(device_B,B,size,cudaMemcpyHostToDevice);

//launch cuda kernel
int threadsPerBlockVec = 256;
int blocksPerGridVec = (n+threadsPerBlockVec-1)/threadsPerBlockVec;
add<<<blocksPerGridVec,threadsPerBlockVec>>> addVector(device_A,device_B,device_C);

//copy data from device to host 
cudaMemcpy(C,dev_c,size,cudaMemcpyDeviceToHost);

//print ouput/result
printVector(c,n);

//free previously allocated device memory 
cudaFree(device_A);
cudaFree(device_B);
cudaFree(device_C);

//free previously allocated host memory 
cudaFreeHost(A);
cudaFreeHost(B);
cudaFreeHost(C);


//=============Matrix multiplication================

int *D, *E,*F;
size_t matrix_size = n*n*sizeof(int);

//allocate memory to host
cudaMAllocHost(&D,matrix_size);
cudaMallocHost(&E,matrix_size);
cudaMallocHost(&F,matrix_size);

initializeMatrix(D, matrixSize);
initializeMatrix(E, matrixSize);

printf("\nMatrix D: \n");
printMatrix(D, matrixSize);

printf("Matrix E: \n");
printMatrix(E, matrixSize);

int *d_D,*d_E,*d_F;

//allocate device memory to D,E and F matrix
cudaMalloc(&d_D,size);
cudaMalloc(&d_E,size);
cudaMAlloc(&d_F,size);


cudaMemcpy(d_D, D, matrix_size, cudaMemcpyHostToDevice);
cudaMemcpy(d_E, E, matrix_size, cudaMemcpyHostToDevice);

int threadsPerBlockMat = 2;
int blocksPerGridMat = (matrix_size + threadsPerBlockMat - 1) / threadsPerBlockMat;

dim3 threadsMat(threadsPerBlockMat, threadsPerBlockMat);
dim3 blocksMat(blocksPerGridMat, blocksPerGridMat);

multiply<<<blocksMat, threadsMat>>>(d_D, d_E, d_F, matrix_size);

cudaMemcpy(F, s_F, matrix_size, cudaMemcpyDeviceToHost);
printf("Multiplication: \n");
printMatrix(F, matrix_size);

free(D);
free(E);
free(F);

cudaFree(d_D);
cudaFree(d_E);
cudaFree(d_F);

    return 0;
}


// nvcc programName.cu - o programName
// ./programName or programName
