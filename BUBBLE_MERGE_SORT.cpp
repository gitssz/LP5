#include <iostream>
#include <vector>
#include <omp.h>
#include <chrono>
using namespace std;

void swapVector(int &a, int &b){
    int temp;
    temp=a;
    a=b;
    b=temp;
}

//======================BUBBLE SORT========================

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

//======================MERGE SORT========================

void mergeSort(vector<int> &arr,int i,int j);
void merge(vector<int> &arr,int i1,int i2,int j1,int j2);

void mergeSort(vector<int> &arr,int i,int j){
   
   int mid;
    if(i<j){

        mid=(i+j)/2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                mergeSort(arr,i,mid);
            }

            #pragma omp section
            {
                mergeSort(arr,(mid+1),j);
            }
        }
        
        merge(arr,i,mid,(mid+1),j);
    }
}


void merge(vector<int> &arr,int i1,int i2,int j1,int j2){

    int left=i1;
    int right=j1;
    int k=0;
    vector<int> temp(arr.size());
     
    while(left<=i2 && right<=j2)
    {
        if(arr[left]<arr[right]){
            temp[k]=arr[left];
            k++;left++;
        }
        else{
            temp[k] =arr[right];
            k++;right++;
        }
    }

        //adding the remaining of the left array into temp
        while(left<=i2){
            temp[k++]=arr[left++];
        }

        //adding remaining of right array into temp
        while(right<=j2){
            temp[k++]=arr[right++];
        }

        //copying sorted array into temporary array
        for(int q=i1,p=0;q<=j2;q++,p++){
            arr[q]=temp[p];
        }
}



int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    
    vector<int> arr_merge = arr; // Make a copy of the original array for merge sort

    // Parallel bubble sort
    double start = omp_get_wtime();
    bubbleSort(arr);
    double finish = omp_get_wtime();

    cout<<"BUBBLE SORT"<<endl;
    for (int i = 0; i < n; i++)
    {
        cout <<arr[i]<<"\t";     
    }
    cout << "\nTime taken for parallel bubble sort: " << finish-start << " milliseconds" << endl;
    
    // Parallel merge sort
    start = omp_get_wtime();
    mergeSort(arr_merge, 0, n-1);
    finish = omp_get_wtime();
    
    cout<<"Merge SORT"<<endl;
    for (int i = 0; i < n; i++)
    {
        cout <<arr_merge[i]<<"\t";     
    }
    cout << "\nTime taken for parallel merge sort: " << finish-start << " milliseconds" << endl;
    
    return 0;
}
