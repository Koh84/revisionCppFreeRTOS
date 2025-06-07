#include <iostream>
#include <stdio.h>

using namespace std;

int area(int length, int breadth) {
    return length * breadth;
}

int perimeter(int length, int breadth) {
    return 2 * length * breadth;
}

int main() {

    int length = 0, breath = 0;
    printf("Enter length and breath");
    cin>>length>>breath;

    int a = area(length, breath);
    int peri = perimeter(length, breath);

    printf("Area :%d\n Perimeter :%d\n", a, peri);
    return 0;
}