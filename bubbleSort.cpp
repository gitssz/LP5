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
        int first =i%2;     //imp for parallelisation
    #pragma omp parallel for shared(arr,first)

        for(int j=first;j<arr.size()-1;j++){
            if(arr[j]>arr[j+1]) {
                swapVector(arr[j],arr[j+1]);
            }
        }
    }
}



int main(){

int n;
cout<<"enter no. of elements: ";
cin>>n;

vector<int> arr(n);
cout<<"enter the array elements: "<<endl;
for(int i=0;i<n;i++){
    cin>>arr[i];
}

bubbleSort(arr);
cout<<"after bubble sort->"<<endl;
for(int i=0;i<n;i++){
    cout<<arr[i];
}


    return 0;
}