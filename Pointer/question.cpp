#include<iostream>
using namespace std;

void changePointer(int **pp) {
    *pp = new int;
    **pp = 88;
}

int main() {

    int a = 3;
    int *p;
    p=&a; 
    
    changePointer(&p);  // pass address of the pointer

    return 0;
}