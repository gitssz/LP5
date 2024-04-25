#include<iostream>
#include<vector>
#include<omp.h>
using namespace std;

void swapVector(int &a, int &b){
    int temp;
    temp=a;
    a=b;
    b=temp;
}

void bubbleSort(vector<int> &arr){

    for(int i=0;i<arr.size();i++){
        int first =i%2;     // for parallelisation
    
        #pragma omp parallel for shared(arr,first)

        for(int j=first;j<arr.size()-1;j++){
            if(arr[j]>arr[j+1]) {
                swapVector(arr[j],arr[j+1]);
            }
        }
    }
}

int main(){

double start_time,finish_time,execution_time;

int n;
cout<<"enter no. of elements: ";
cin>>n;

vector<int> arr(n);
cout<<"enter the array elements: "<<endl;
for(int i=0;i<n;i++){
    cin>>arr[i];
}

start_time=omp_get_wtime();

bubbleSort(arr);
cout<<"after bubble sort->"<<endl;
for(int i=0;i<n;i++){
    cout<<arr[i];
}

finish_time=omp_get_wtime();
execution_time=finish_time-start_time;


cout<<"\nexecution time of parallel bubble sort is: "<<execution_time<<"s"<<endl;

    return 0;
}
// g++ -fopenmp filename.cpp -o filename
// ./filename
