#include <iostream>
using namespace std;

int main() {

    cout<<"Classic 1"<<endl;
    int A[3][4];
    for(int i=0; i<3; i++) {
        for(int j=0; j<4; j++) {
            A[i][j] = j;
        }
    }

    for(int i=0; i<3; i++) {
        for(int j=0; j<4; j++) {
            cout<<A[i][j]<<" ";
        }
        cout<<endl;
    }

    cout<<"Classic 2"<<endl;
    int B[3][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};

    for(int i=0; i<3; i++) {
        for(int j=0; j<4; j++) {
            cout<<B[i][j]<<" ";
        }
        cout<<endl;
    }

    cout<<"Heap partial"<<endl;
    int *C[3];
    C[0] = new int[4];
    C[1] = new int[4];
    C[2] = new int[4];

    for (int i = 0; i < 3; ++i) {
        delete[] C[i];
        C[i] = nullptr; // optional: prevents dangling pointers
    }

    cout<<"Heap pointer"<<endl;
    int **D;
    D = new int*[3];
    D[0] = new int[4];
    D[1] = new int[4];
    D[2] = new int[4];

    for(int i=0; i<3; i++) {
        for(int j=0; j<4; j++) {
            D[i][j] = j*2;
        }
    }

    for(int i=0; i<3; i++) {
        for(int j=0; j<4; j++) {
            cout<<D[i][j]<<" ";
        }
        cout<<endl;
    }

    return 0;
}