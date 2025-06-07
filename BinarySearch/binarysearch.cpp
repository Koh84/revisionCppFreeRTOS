#include<iostream>
using namespace std;

struct Array {
    int A[10];
    int size;
    int length;
};

void Display(Array arr) {
    for(int i=0; i<arr.length; i++)
        cout<<arr.A[i]<<" ";
}

int BinarySearch(struct Array arr, int k) {

    int l,h,m;
    l = 0;
    h = arr.length;
    
    while(l<=h) {
        m = (l+h)/2;
        if(arr.A[m] == k) {
            return m;
        } else if (k<arr.A[m]) {
            h = m-1;
        } else {
            l = m+1;
        }
    }

    return -1;
}

int rBinarySearch(struct Array arr, int l, int h, int k) {

    int m;    
    while(l<=h) {
        m = (l+h)/2;
        if(arr.A[m] == k) {
            return m;
        } else if (k<arr.A[m]) {
            h = m-1;
            return rBinarySearch(arr, l, h, k);
        } else {
            l = m+1;
            return rBinarySearch(arr, l, h, k);
        }
    }

    return -1;
}

int main(){
    Array arr = {{1,2,3,4,5}, 10, 5};

    int index = BinarySearch(arr, 5);
    cout<<"Index :"<<index<<endl;

    int rindex = rBinarySearch(arr, 0, arr.length, 5);
    cout<<"rIndex :"<<rindex<<endl;

    Display(arr);
    return 0;
}