#include<iostream>
#include<omp.h>
using namespace std;
void merge(int arr[],int low,int mid,int high){
    int n1=mid-low+1;
    int n2=high-mid;

    int left[n1];
    int right[n2];

    for(int i=0;i<n1;i++){
        left[i]=arr[low+i];
    }
    for(int i=0;i<n2;i++){
        right[i]=arr[mid+i+1];
    }
    int i=0,j=0,k=low;
    while(i<n1 && j<n2){
        if(left[i] <= right[j]){
            arr[k]=left[i];
            i++;
        }else{
            arr[k]=right[j];
            j++;
        }
        k++;
    }

    while(i<n1){
        arr[k]=left[i];
        i++;
        k++;
    }

    while(j<n2){
        arr[k]=right[j];
        j++;
        k++;
    }




}



void mergeSort(int arr[],int low,int high){
    if(low<high){
        int mid=(low+high)/2;
        mergeSort(arr,low,mid);
        mergeSort(arr,mid+1,high);
        merge(arr,low,mid,high);
    }
}

void parallel_Merge(int arr[],int low,int high){
    if(low<high){
        int mid=(low+high)/2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                parallel_Merge(arr,low,mid);
            }
            #pragma omp section
            {
                parallel_Merge(arr,mid+1,high);
            }

        }
        merge(arr,low,mid,high);
    }
}

void simpleBubble(int arr[],int n){
    for(int i=0;i<n-i;i++){
        for(int j=0;j<n-i-1;j++){
            if(arr[j] > arr[j+1]){
                swap(arr[j],arr[j+1]);
            }
        }
    }
}

void parallel_Bubble(int arr[],int n){
    for(int i=0;i<n;i++){
        #pragma omp for
        for(int j=1;j<n;j+=2){
            if(arr[j] < arr[j-1]){
                swap(arr[j],arr[j-1]);
            }
        }
        #pragma omp barrier
        #pragma omp for
        for(int j=2;j<n;j+=2){
            if(arr[j] < arr[j-1]){
                swap(arr[j],arr[j-1]);
            }
        }

    }
}
int main(){

    int n;
    cout<<"\nEnter the array element";
    cin>>n;
    cout<<"\nEnter array ele";
    int arr[n];
    int arrB[n];
    int arrC[n];
    int arrD[n];
    for(int i=0;i<n;i++){
        int x;
        cin>>x;
        arr[i]=x;
        arrB[i]=x;
        arrC[i]=x;
        arrD[i]=x;
    }

    mergeSort(arr,0,n-1);
    parallel_Merge(arrB,0,n-1);
    simpleBubble(arrC,n);
    parallel_Bubble(arrD,n);


    cout<<"simple merge\n";
    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }


    cout<<"\nparallel array\n";
    for(int i=0;i<n;i++){
        cout<<arrB[i]<<" ";
    }

     cout<<"\nsimple bubble\n";
    for(int i=0;i<n;i++){
        cout<<arrC[i]<<" ";
    }

      cout<<"\nparallel bubble\n";
    for(int i=0;i<n;i++){
        cout<<arrD[i]<<" ";
    }
    




}