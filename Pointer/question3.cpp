#include <iostream>
using namespace std;

void byValue(int *p) {
    *p = 1;
    cout<<"*p2 byValue :"<<*p<<endl;
}

int main(){

    int a = 3;
    int *p2;
    p2 = &a;

    cout<<"*p2 main 1:"<<*p2<<endl;
    byValue(p2);
    cout<<"*p2 main 1:"<<*p2<<endl;
    return 0;
}