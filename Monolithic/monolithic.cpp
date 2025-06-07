#include <iostream>
#include <stdio.h>

using namespace std;

int main() {

    int length = 0, breath = 0;
    printf("Enter length and breath");
    cin>>length>>breath;

    int area = length * breath;
    int peri = 2 * (length + breath);

    printf("Area :%d\n Perimeter :%d\n", area, peri);
    return 0;
}