#include<iostream>
#include<omp.h>
#include<vector> 
#include<climits>
using namespace std;

void min_reduction(vector<int> &arr){

	int min_value= INT_MAX;
	#pragma omp parallel for reduction(min:min_value) //NOTE- NO ; AT THE END OF OPEN MP DIRECTIVE
	for(int i=0;i<arr.size() ;i++){
		if(min_value > arr[i]){
		min_value=arr[i];
		}
		
	}
	cout<<"Minimum value is "<<min_value<<endl;
}



void max_reduction(vector<int> &arr){


	int max_value =INT_MIN;
	#pragma parallel for reduction(max:max_value)
	for(int i=0; i<arr.size(); i++){
	
		if(max_value< arr[i]){
			max_value =arr[i];
		}
	}

cout<< "maximum value is "<<max_value<<endl;
}

void sum_reduction(vector<int> &arr){

	int sum_value=0;
	#pragma omp parallel for reduction(+:sum_value)
	for(int i=0;i<arr.size() ;i++){
		sum_value+=arr[i];
}
cout<<"sum is "<<sum_value<<endl;
}

void avg_reduction(vector<int> &arr){

	int sum=0;
	#pragma omp parallel for reduction(+:sum)
	for(int i=0;i<arr.size();i++){
		sum+=arr[i];
	}
cout<<"average is "<<double(sum)/arr.size()<<endl;

}


int main(){

// vector<int> nums= {5,2,6,1,7,0,3};

int n;
cout<<"enter number of elements in array: ";
cin>>n;

vector<int> nums(n);
cout<<endl<<"enter array elements: "<<endl;
for(int i=0;i<n;i++){
	cin>>nums[i];
}

min_reduction(nums);
max_reduction(nums);
sum_reduction(nums);
avg_reduction(nums);

return 0;

}