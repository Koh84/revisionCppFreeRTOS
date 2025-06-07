#include <iostream>
#include <stdio.h>

using namespace std;

class Rectangle {
    private:
    int length;
    int breadth;

    public:
    //default constructor
    Rectangle() {
        length = 0; 
        breadth = 0;
    }
    //constructor overloading
    Rectangle(int l, int b);

    ~Rectangle();

    int area();

    int perimeter();

    //Accessor function
    int getLength() {
        return length;
    }
    //Mutator function
    void setLength(int l) {
        length = l;
    }

    //Accessor function
    int getBreadth() {
        return breadth;
    }
    //Mutator function
    void setBreadth(int l) {
        breadth = l;
    }
};

Rectangle::Rectangle(int l, int b) {
    length = l;
    breadth = b;
}

Rectangle::~Rectangle() {
    cout<<"Destructor"<<endl;
}

int Rectangle::area() {
    return length * breadth;
}

int Rectangle::perimeter() {
    return 2 * length * breadth;
}

int main() {
   
    Rectangle r(0,0);

    printf("With oop function");
    int l, b;
    printf("Enter length and breadth");
    cin>>l>>b;

    r.setLength(l);
    r.setBreadth(b);

    int a = r.area();
    int peri = r.perimeter();

    printf("Area :%d\n Perimeter :%d\n", a, peri);
    return 0;
}