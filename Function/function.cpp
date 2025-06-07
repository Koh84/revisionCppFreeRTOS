#include <stdio.h>
#include <iostream>
using namespace std;

int add(int a, int b) {
    int c;
    c = a + b;
    return c;
}

int main() {

    int x = 1;
    int y = 2;
    int z = 0;

    z = add(x, y);
    cout << z << endl;

    return 0;
}