#include<iostream>
using namespace std;

class Node {
public:
    int data;
    Node *next;
};

class LinkedList {
private:
    Node *first;
public:
    LinkedList() {
        first = NULL;
    }

    //LinkedList(int A[], int n);
    ~LinkedList();

    void Display();
    void Insert(int index, int x);
    int Delete(int index);
    int Length();
};

LinkedList::~LinkedList() {
    Node *p = first;
    while(first){
        first= first->next;
        delete p;
        p = first;
    }
}

int LinkedList::Length() {
    Node *node = first;
    int len = 0;
    while(node){
        len++;
        node = node->next;
    }
    return len;
}

void LinkedList::Insert(int index, int x){

    Node* t, *p = first;

    if(index <0 || index > Length()) {
        return;
    }

    t = new Node;
    t->data = x;
    t->next = NULL;

    if(index == 0) {
        t->next = first;
        first = t;
        return;
    } else {
        for(int i=0; i<index-1; i++){
            p = p->next;
        }
        t->next = p->next;
        p->next = t;
    }
}

void LinkedList::Display(){
    Node *node = first;
    while(node) {
        cout<<node->data<<" "<<endl;
        node = node->next;
    }
}

int LinkedList::Delete(int index){
    Node *p, *q;
    int x = -1;

    if(index <0 || index > Length()) {
        return x;
    }

    if(index == 1) {
        p = first;
        first = p->next;
        x = p->data;
        delete(p);
    } else {
        p = first;
        for(int i=0; i<index-1; i++) {
            q = p;
            p = p->next;
        }
        x = p->data;
        q->next = p->next;
        delete(p);
    }
    return x;
}

int main(){

    LinkedList *ll = new LinkedList();

    ll->Insert(0, 10);
    ll->Insert(1, 20);
    ll->Insert(2, 30);
    ll->Insert(3, 40);
    ll->Insert(4, 50);
    ll->Insert(0, 60);
    ll->Delete(2);
    ll->Display();

    return 0;
}