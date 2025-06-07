#include <iostream>
using namespace std;

void byValueP(int *p){
    *p = 3;
    *(p+1) = 4;
    cout<<"p[0] byValueP:"<<p[0]<<endl;
    cout<<"p[1] byValueP:"<<p[1]<<endl;
}

int main(){
    int *p = new int[2];
    p[0] = 1;
    p[1] = 2;

    cout<<"p[0] main:"<<p[0]<<endl;
    cout<<"p[1] main:"<<p[1]<<endl;

    byValueP(p);

    cout<<"p[0] main:"<<p[0]<<endl;
    cout<<"p[1] main:"<<p[1]<<endl;
    cout<<"------"<<endl;

    return 0;
}