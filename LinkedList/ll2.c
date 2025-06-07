#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node * next;
} *first = NULL;


int count(struct Node *p) {
    int c = 0;
    while(p) {
        c++;
        p = p->next;
    }
    return c;
}

void display(struct Node *p) {

   while(p) {
    printf("%d ", p->data);
    p = p->next;
   }
}

void insert(struct Node *p, int pos, int val) {

    if(pos<0 || pos> count(p)) {
        return;
    }

    struct Node *t = (struct Node *)malloc(sizeof(struct Node));
    t->data = val;

    if (pos == 0){
        t->next = first;
        first = t;
    } else {
        for(int i=0; i<pos-1; i++) {
            p=p->next;
        }
        t->next = p->next;
        p->next = t;
    }
}

int main() {
    int size = count(first);
    printf("size : %d\n", size);

    insert(first, 0, 20);
    insert(first, 1, 30);
    insert(first, 2, 40);

    display(first);

    size = count(first);
    printf("size : %d\n", size);
    
    return 0;
}
