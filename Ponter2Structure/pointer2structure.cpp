#include <stdio.h>
#include <iostream>

using namespace std;

struct Rectangle {
    int length;
    int breadth;
};

int main() {
    cout << " C style syntax" << endl;

    struct Rectangle *r1;
    //r1 = (struct Rectangle*)malloc(sizeof(r1)); ok
    r1 = (struct Rectangle*)malloc(sizeof(struct Rectangle));

    r1->length = 10;
    r1->breadth = 1;

    cout << r1->length << endl << r1->breadth << endl; 

    delete r1;

    cout << " C++ style syntax" << endl;

    Rectangle *r2;
    r2 = new Rectangle[sizeof(r2)];

    r2->length = 100;
    r2->breadth = 10;

    cout << r2->length << endl << r2->breadth << endl; 

    delete r2;

    Rectangle r3 = {1, 2};
    Rectangle *p = &r3;

    cout << p->length << endl << p->breadth << endl; 

    cout << " C++ style syntax" << endl;

    Rectangle *r4;
    r4 = new Rectangle;

    r4->length = 100;
    r4->breadth = 10;

    cout << r4->length << endl << r4->breadth << endl; 

    delete r4;


    return 0;
}