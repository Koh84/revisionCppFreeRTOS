#include <iostream>

using namespace std;

int main() {
    int A[5];
    A[0] = 1;
    A[1] = 2;
    A[2] = 3;

    cout<<sizeof(A)<<endl;
    cout<<A[0]<<endl;
    printf("%d\n", A[1]);

    cout<<"B-------"<<endl;

    int B[5] = {3, 5, 7, 8, 9};

    cout<<sizeof(B)<<endl;
    cout<<B[0]<<endl;
    cout<<B[1]<<endl;

    cout<<"C-------"<<endl;

    int C[] = {3, 5, 7, 8, 9, 0, 2};

    cout<<sizeof(C)<<endl;
    cout<<C[0]<<endl;
    cout<<C[1]<<endl;

    cout<<"D-------"<<endl;

    int D[10] = {3, 5, 7, 8, 9, 0, 2};

    cout<<sizeof(D)<<endl;
    cout<<D[8]<<endl;
    cout<<D[9]<<endl;

    cout<<"E-------"<<endl;

    int E[10] = {0};

    cout<<sizeof(E)<<endl;
    cout<<E[8]<<endl;
    cout<<E[9]<<endl;

    cout<<"E1-------"<<endl;
    for (int i=0; i<sizeof(E)/sizeof(E[0]); i++)
    {
        cout<<E[i]<<endl;
    }

    cout<<"E2-------"<<endl;
    for (int i=0; i<size(E); i++)
    {
        cout<<E[i]<<endl;
    }

    cout<<"E3-------"<<endl;
    for (int x: E)
    {
        cout<<x<<endl;
    }

    int n;
    cout<<"Enter size"<<endl;
    cin>>n;
    //int F[n] = {3, 5, 7, 8, 9, 0, 2}; //error
    int F[n];
    F[0] = 1;
    F[1] = 2;
    F[2] = 3;

    cout<<"F-------"<<endl;
    for (int x: F)
    {
        cout<<x<<endl;
    }

    return 0;
}