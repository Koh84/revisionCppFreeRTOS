#include <iostream>
using namespace std;

int main() {

    int A[5] = { 1,2,3,4,5 };
    int *p, *q;

    p = new int[5];
    p[0] = 3;
    p[1] = 5;
    p[2] = 7;
    p[3] = 9;
    p[4] = 11;

    for(int i=0; i<5; i++) {
        cout<<p[i]<<endl;
    }

    q = new int[10];

    for(int i=0; i<5; i++) {
       q[i] = p[i];
    }

    delete []p;
    p = q;

    q = nullptr;


    for(int i=0; i<10; i++) {
        cout<<p[i]<<endl;
    }

    delete []q;
    p = nullptr;
    return 0;
}