#include <iostream>
using namespace std;


void byValue(int *p){
    *p = 2;
    cout<<"p in byValue:"<<*p<<endl;
}


int main() {
    int *p = new int;
    *p = 1;
    cout<<"p in main:"<<*p<<endl;
    byValue(p);
    cout<<"p in main:"<<*p<<endl;
    return 0;
}