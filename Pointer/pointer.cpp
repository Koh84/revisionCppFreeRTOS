#include <stdio.h>
#include <iostream>

using namespace std;

struct Rectangle {
    int length;
    int breadth;
    char x;
};

int main() {

    int a = 10;
    int *p;

    p = &a;

    cout << a << endl;

    cout << p << endl;
    cout << *p << endl;

    *p = 100;
    cout << &a << endl;
    cout << p << endl;
    cout << *p << endl;

    int A[5] = {2, 4, 6, 8, 10};

    p = A;

    cout <<"------ print using array"<< endl;
    cout << p[0] << endl;
    cout << p[1] << endl;
    cout << p[4] << endl;

    cout <<"------ print using pointer"<< endl;
    cout << *(p) << endl;
    cout << *(p+1) << endl;
    cout << *(p+4) << endl;

    cout <<"------ print using pointer for loop"<< endl;

    for(int i=0; i<sizeof(A)/sizeof(A[0]) ; i++){
        cout << *(p+i) << endl; 
    }

    cout <<"------ print using pointer for loop using size"<< endl;

    for(int i=0; i<size(A) ; i++){
        cout << *(p+i) << endl; 
    }

    cout <<"------ C style - print using pointer for loop using size on variable B on Heap"<< endl;

    int B[5] = {20, 40, 60, 80, 100};
    int *q;
    q = (int *)malloc(sizeof(B));

    for(int i=0; i<size(B) ; i++){
        *(q+i) = B[i];
        cout << "array address on stack :" << &B[i] << endl; 
        cout << "pointer address on heap :" << q+i << endl; 
        cout << *(q+i) << endl; 
    }

    free(q);

    cout <<"------ C++ style - print using pointer for loop using size on variable C on Heap"<< endl;

    int C[5] = {20, 40, 60, 80, 100};
    int *r;
    r = new int[5];

    for(int i=0; i<size(C) ; i++){
        *(r+i) = C[i];
        cout << "array address on stack :" << &C[i] << endl; 
        cout << "pointer address on heap :" << r+i << endl; 
        cout << *(r+i) << endl; 
    }

    delete [] r;

    cout <<"------ Interesting thing about size of pointer in new compiler"<< endl;

    int *p1;
    char *p2;
    float *p3;
    double *p4;
    struct Rectangle *p5;

    cout<<sizeof(p1)<<endl;
    cout<<sizeof(p2)<<endl;
    cout<<sizeof(p3)<<endl;
    cout<<sizeof(p4)<<endl;
    cout<<sizeof(p5)<<endl;
    return 0;
}