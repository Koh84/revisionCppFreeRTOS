#include <stdio.h>
#include <stdlib.h>


struct Node {
    int data;
    struct Node * next;
};

struct Node * createNode(int x) {
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->data = x;
    temp->next = NULL;

    return temp;
}

void append(struct Node **head_ref, int x){
    struct Node *node = createNode(x);

    if(*head_ref == NULL) {
        *head_ref = node;
        return;
    }

    struct Node *temp = *head_ref;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = node;
}

void printList(struct Node *node) {
    while(node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
}

struct Node getRemoveFirst(struct Node **head_ref) {
    struct Node result = {0, NULL};
    if(*head_ref == NULL)
        return result;

    struct Node *temp = *head_ref;
    result.data = (*head_ref)->data;
    *head_ref = (*head_ref)->next;
    free(temp);
    temp = NULL;

    return result;
}

int main() {
    struct Node *head = NULL;

    append(&head, 11);
    append(&head, 22);
    append(&head, 33);
    printList(head);

    struct Node removed = getRemoveFirst(&head);
    printf("%d ", removed.data);

    return 0;
}
