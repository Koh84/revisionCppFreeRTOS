#include <stdio.h>
#include <iostream>

using namespace std;

void fun (int A[], int n) {
    //cout<<sizeof(A)/sizeof(int)<<endl;
    for(int i=0; i<n; i++) {
        cout<<A[i]<<endl;
    }
    A[0] = 10;
}

int * fun1 (int size) {
    int *p;
    p = (int *)malloc(size * sizeof(int));
    for(int i=0; i<size; i++) {
        p[i] = i;
    }
    return p;
}

int main() {

    int A[] = {1, 2, 3, 4, 5};

    // for(int x: A) {
    //     cout<<x<<endl;
    // }

    fun(A, sizeof(A)/sizeof(int));
    cout<<A[0]<<endl;


    int *B;
    B = fun1(5);

    for(int i=0; i<5; i++) {
       cout<<B[i]<<endl;
    }

    return 0;
}