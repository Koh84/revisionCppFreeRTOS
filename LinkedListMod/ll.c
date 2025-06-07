#include <stdio.h>
#include <stdlib.h>

// Define a node
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to print the linked list
void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Function to append a node at the end
void append(struct Node** head_ref, int new_data) {
    struct Node* new_node = createNode(new_data);
    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }
    struct Node* last = *head_ref;
    while (last->next != NULL)
        last = last->next;
    last->next = new_node;
}

// Function to remove the first node and return a copy of it
struct Node getAndRemoveFirst(struct Node** head_ref) {
    struct Node result = {0, NULL};

    if (*head_ref == NULL) {
        return result; // empty list
    }

    struct Node* temp = *head_ref;
    result.data = temp->data;

    *head_ref = temp->next;
    free(temp);

    return result;
}

// Main function
int main() {
    struct Node* head = NULL;

    append(&head, 10);
    append(&head, 20);
    append(&head, 30);

    printf("Linked List: ");
    printList(head);

    struct Node removed = getAndRemoveFirst(&head);
    printf("Removed: %d\n", removed.data);

    return 0;
}
