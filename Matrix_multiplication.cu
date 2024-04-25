#include<iostream>
#include<runtime_cuda.h>


__global__  void matrixMultiplication(int *a, int*b,int *c,int n){

    int row= blockIdx.y+ blockDim.y +threadIdx.y;
    int col= blockIdx.x +blockDim.x +threadIdx.x;

    if(row<n && col<n){
        int product_value=0;
        for(int k=0;k<n;k++){
            product_value += a[row*n+k] *  b[k*n+col];
        }
        c[row*n+col]=product_value;
    }
} 



int main(){


int n=512;
int size = n*n*sizeof(int);

int *A,*B,*C;
int *d_A,*d_B,*d_C;


//allocate host memory to matrix A,B and C
cudaMallocHost(&A,size);
cudaMallocHost(&B,size);
cudaMallocHost(&C,size);

//allocate device memory to A,B and C matrix
cudaMalloc(&d_A,size);
cudaMalloc(&d_B,size);
cudaMAlloc(&d_C,size);


//initialize matrix A and B
for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
        A[i*n+j]= i*n+j ;
        B[i*n+j]=j*n+i;
    }
}

//copy matrix A and B from host to Device
cudaMemcpy(d_A,A,size,cudaMemcpyHostToDevice);
cudaMemcpy(d_B,B,size,cudaMemcpyHostToDevice);

// defining  block and grid size
dim3 dimBlock(16,16);
dim3 dimGrid(n/dimBlock.x,n/dimBlock.y);

//launch kernel
matrixMultiplication<<<dimGrid,dimBlock>>>(dev_A,dev_B,dev_C,n);

//copy result to the host 
cudaMemcpy(C,dev_C,size,cudaMemcpyDeviceToHost);


//print result
for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
        cout<<C[i*n+j]<<" ";
    }
    cout<<endl;
}


//free device memory
cudaMemcpy(d_A);
cudaMemcpy(d_B);
cudaMemcpy(d_C);


// free host memory 
cudaMemcpyHost(A);
cudaMemcpyHost(B);
cudaMemcpyHost(C);

    return 0;
}


// nvcc programName.cu - o programName
// ./programName or programName
