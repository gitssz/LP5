#include<iostream>
#include<vector>
#include<omp.h>
using namespace std;

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



int main(){

int n;
cout<<"enter number of elements: "<<endl;
cin>>n;

vector <int> arr(n);
cout<<"enter vector elements: "<<endl;
for(int i=0;i<n;i++){
    cin>>arr[i];
}

double start_time,finish_time,execution_time;
start_time = omp_get_wtime();

mergeSort(arr,0,n-1);

finish_time=omp_get_wtime();
cout<<"sorted vector ->"<<endl;

for(int i=0;i<n;i++){   
    cout<<arr[i]<<" ";
}

execution_time=finish_time-start_time;
cout<<"\nexecution time of merge sort in parallel "<<execution_time<<"s"<<endl;
    return 0;
}
