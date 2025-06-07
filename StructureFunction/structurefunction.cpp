#include <iostream>
#include <stdio.h>

using namespace std;

struct Rectangle {
    int length;
    int breadth;
};

void initialise(struct Rectangle *r, int l, int b) {
    r->length = l;
    r->breadth = b;
}

int area(struct Rectangle r) {
    return r.length * r.breadth;
}

int perimeter(struct Rectangle r) {
    return 2 * r.length * r.breadth;
}

int main() {
    Rectangle r = {0, 0};

    printf("With initiliase function");
    int l, b;
    printf("Enter length and breadth");
    cin>>l>>b;

    initialise(&r, l, b);

    int a = area(r);
    int peri = perimeter(r);

    printf("Area :%d\n Perimeter :%d\n", a, peri);
    return 0;
}