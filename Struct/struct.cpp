#include <stdio.h>
#include <iostream>
//#include <format>

using namespace std;

struct Rectangle {
    int length;
    int breadth;
    char x;
} r3, r4;

struct Rectangle r2;

int main() {

    struct Rectangle r1 ={10,5};
    printf("length : %d\n", r1.length);
    printf("breadth : %d\n", r1.breadth);
    printf("size : %lu\n", sizeof(r1));

    //r3 = {1, 3}; //error

    r3.length = 1;
    r3.breadth = 2;
    cout << "length: "<<r3.length<<", bread: "<<r3.breadth<<endl;
    //c++20 only
    //cout << format("length {} breadth {}\n", r3.length, r3.breadth);
    return 0;
}