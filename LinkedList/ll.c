#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node * next;
} *first = NULL;


void create(int A[], int size) {
    int i;
    struct Node *t, *last;
    first = (struct Node *)malloc(sizeof(struct Node));
    first->data = A[0];
    first->next = NULL;
    last = first;

    for(i=1; i<size; i++) {
        t = (struct Node *)malloc(sizeof(struct Node));
        t->data = A[i];
        t->next = NULL;
        last->next = t;
        last = t;
    }
}

void display(struct Node *p) {

   while(p) {
    printf("%d ", p->data);
    p = p->next;
   }
}

int main() {
    int A[] = { 1,2,3,4,5 };
    create(A, 5);

    display(first);
    
    return 0;
}
