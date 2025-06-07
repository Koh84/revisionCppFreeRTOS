#include <iostream>
using namespace std;

struct Node {
    int data;
    struct Node * next;
};

void append(Node **head_ref, int x){
    Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->data = x;
    node->next = NULL;

    if(*head_ref == NULL) {
        *head_ref = node;
        return;
    }
}

int main(){
    Node *head = NULL;

    append(&head, 1);
    cout<<"head->data :"<<head->data<<endl;
    
    return 0;
}