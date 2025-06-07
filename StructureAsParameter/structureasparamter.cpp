#include <stdio.h>
#include <iostream>

using namespace std;

struct Rectangle {
    int length;
    int breadth;
    char x;
};

void fun (struct Rectangle r1) {
    r1.length = 10;
    cout<< "function call:" << endl << r1.length << endl << r1.breadth <<endl;
}

void funAddress (struct Rectangle *r1) {
    r1->length = 10;
    cout<< "function call:" << endl << r1->length << endl << r1->breadth <<endl;
}


int main() {

    struct Rectangle r = { 1, 2 };
    cout<< "main call1:" << endl << r.length << endl << r.breadth <<endl;
    fun(r);
    cout<< "main call2:" << endl << r.length << endl << r.breadth <<endl;
    funAddress(&r);
    cout<< "main call3:" << endl << r.length << endl << r.breadth <<endl;
    return 0;
}