#include<iostream>
#include<bits/stdc++.h>
#include<omp.h>
using namespace std;

int minValue(int arr[],int n){
    int minval=arr[0];
    #pragma omp parallel for reduction(min : minval)
    for(int i=0;i<n;i++){
        if(minval > arr[i]){
            minval=arr[i];
        }
    }
    return minval;
}

int maxValue(int arr[],int n){
    int maxval=arr[0];
    #pragma omp parallel for reduction(max : maxval)
    for(int i=0;i<n;i++){
        if(maxval < arr[i]){
            maxval=arr[i];
        }
    }
    return maxval;
}

int sum(int arr[],int n){
    int sum=0;
    #pragma omp parallel for reduction(+ : sum)
    for(int i=0;i<n;i++){
        sum+=arr[i];
    }
    return sum;
}

int average(int arr[],int n){
    int answer=sum(arr,n);
    return answer/n;
}

int main(){

    int n;
    cout<<"\nEnter the number of elements";
    cin>>n;
    cout<<"\nEnter the array elements";
    int arr[n];
    for(int i=0;i<n;i++){
        int x;
        cin>>x;
        arr[i]=x;
    }

    cout<<"\nMin Value = "<<minValue(arr,n);
    cout<<"\nMax Value = "<<maxValue(arr,n);
    cout<<"\nSum Value = "<<sum(arr,n);
    cout<<"\nAverage Value = " <<average(arr,n);

    return 0;


}