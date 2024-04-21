#include<iostream>
#include<vector>
using namespace std;

void merge(vector<int> &arr, int i1,int i2,int j2, int j3) ;
void mergeSort(vector<int> &arr,int start,int end);


void mergeSort(vector<int> &arr,int start,int end)
{
    int mid;
    if(start<end){

        mid=(start+end)/2;

        mergeSort(arr,start,mid);
        mergeSort(arr,mid+1,end);
        merge(arr,start,mid,mid+1,end);
    }
}


void merge(vector<int> &arr, int i1,int i2,int j1, int j2){

    int left=i1;
    int right=j1;
    int k=0;
    vector<int> temp(arr.size());

    while(left<=i2 && right<=j2){
        
        if(arr[left]<arr[right]){
            temp[k++]=arr[left++];
        }
        else{
            temp[k++] = arr[right++];
        }
    }

    while(left<=i2){
        temp[k++]=arr[left++];
    }

    while(right<=j2){
        temp[k++]= arr[right++];
    }

    //combine
    for(int i=i1,j=0;i<=j2;i++,j++){
        arr[i] =temp[j];
    }



}

int main(){

    vector <int> arr={3,2,4,1};
    int n=arr.size();
    mergeSort(arr,0,n-1);

    cout<<"sorted array-> "<<endl;
    for(int i=0;i<n;i++){
        cout<<arr[i];
    }

    return 0;
}