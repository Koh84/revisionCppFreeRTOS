#include<iostream>
using namespace std;

void byValue(int *pp){
    *pp = 6;
    cout<<"byValue *pp: "<<*pp<<endl;
}

void byValueP(int **qq){
    int *t = new int;
    *t = 7;

    *qq = t;
    cout<<"byValue address *qq: "<<*qq<<endl;
    cout<<"byValue value *qq: "<<**qq<<endl;
}

void byValueR(int *rr){
    *rr = 5;
    cout<<"byValueR *rr: "<<*rr<<endl;
}

void byValueS(int *ss){
    ss[0] = 10;
    ss[4] = 50;
    cout<<"byValueS ss[0]: "<<ss[0]<<endl;
    cout<<"byValueS ss[4]: "<<ss[4]<<endl;
}

int main() {

    int *p = new int;
    *p = 5;
    cout<<"main *p: "<<*p<<endl;
    byValue(p);
    cout<<"main *p: "<<*p<<endl;

    int *q = NULL;

    byValueP(&q);
    cout<<"main *q: "<<*q<<endl;


    int *r;
    *r = 1;
    cout<<"main *r: "<<*r<<endl;
    byValueR(r);
    cout<<"main *r: "<<*r<<endl;

    int *s = new int[5];
    s[0] = 1;
    s[1] = 2;
    s[2] = 3;
    s[3] = 4;
    s[4] = 5;
    cout<<"main s[0]: "<<s[0]<<endl;
    cout<<"main s[4]: "<<s[4]<<endl;
    byValueS(s);
    cout<<"main s[0]: "<<s[0]<<endl;
    cout<<"main s[4]: "<<s[4]<<endl;
    return 0;
}