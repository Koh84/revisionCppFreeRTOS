#include <iostream>
using namespace std;

struct Array {
    int A[10];
    int size;
    int length;
};

void Display(struct Array arr) {
    cout<<"Elements in array are"<<endl;

    for(int i = 0; i< arr.length; i++) {
        cout<<arr.A[i]<< " "<<endl;
    }
}

// void Append(struct Array *arr, int x){
//     if((*arr).length < (*arr).size) {
//         (*arr).A[(*arr).length] = x;
//         (*arr).length++;
//     }
// }

void Append(struct Array *arr, int x){
    if(arr->length < arr->size) {
        arr->A[arr->length] = x;
        arr->length++;
    }
}

void Insert(struct Array *arr, int index, int x) {

    if (index >= 0 && index < arr->length && arr->length < arr->size) {
        for(int i = arr->length; i>index; i--) {
            arr->A[i] = arr->A[i-1];
        }
        arr->A[index] = x;
        arr->length++;
    }
}

int Delete(struct Array *arr, int index) {

    int x = 0;
    if(index>=0 && index < arr->length) {
        x = arr->A[index];
        for(int i=index; i<arr->length-1; i++){
            arr->A[i] = arr->A[i+1];
        }
        arr->length--;
    }
    return x;
}

int main() {
    Array arr = {{1,2,3,4,5}, 10, 5};

    //Append(&arr, 6);
    //Insert(&arr, 0, 9);
    int x = Delete(&arr, 0);
    Display(arr);

    return 0;
}