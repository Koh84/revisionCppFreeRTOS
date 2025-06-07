#include <stdio.h>
#include <iostream>
using namespace std;

/*
    call by value
    a: 2
    x: 1
    call by address
    a1: 1
    a2: 2
    x: 2
    call by reference
    a: 2
    x: 2
*/

int addCallByValue(int a, int b) {
    
    a++;
    cout << "a: " << a << endl;
    return 0;
}

int addCallByAddress(int *a, int *b) {
    
    cout << "a1: " << *a << endl;
    (*a)++;
    cout << "a2: " << *a << endl;
    return 0;
}

int addCallByReference(int &a, int &b) {
    
    a++;
    cout << "a: " << a << endl;
    return 0;
}

int main() {

    int x = 1;
    int y = 2;
    int z = 0;

    cout << "call by value" << endl;
    z = addCallByValue(x, y);
    cout << "x: " << x << endl;

    x = 1;
    y = 2;
    z = 0;
    cout << "call by address" << endl;
    z = addCallByAddress(&x, &y);
    cout << "x: " << x << endl;

    cout << "call by reference" << endl;

    x = 1;
    y = 2;
    z = 0;
    addCallByReference(x, y);
    cout << "x: " << x << endl;
    return 0;
}