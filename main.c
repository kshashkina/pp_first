#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for a node in the linked list
typedef struct Node {
    char data;
    struct Node* next;
} Node;

// Function to create a new node
Node* createNode(char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of the linked list
void insertNodeEnd(Node** head, char data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Function to insert a node at a specific position in the linked list
void insertNodeAtPosition(Node** head, char data, int position) {
    Node* newNode = createNode(data);

    if (position == 0) {
        newNode->next = *head;
        *head = newNode;
    } else {
        Node* current = *head;
        int i;
        for (i = 0; i < position - 1 && current != NULL; i++) {
            current = current->next;
        }
        if (current != NULL) {
            newNode->next = current->next;
            current->next = newNode;
        } else {
            printf("Invalid position.\n");
            free(newNode);
        }
    }
}

// Function to display the linked list
void displayList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%c", current->data);
        current = current->next;
    }
    printf("\n");
}

// Function to free the linked list
void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    int commandNumber;
    Node* newWord = NULL; // Initialize the linked list
    char inputLine[100];
    char fileName[50];

    while (1) {
        printf("Write your command:\n");
        scanf("%d", &commandNumber);
        switch (commandNumber) {
            case 1:
                printf("Enter text to append:\n");
                scanf(" %[^\n]s", inputLine); // Read a line of text
                for (int i = 0; i < strlen(inputLine); i++) {
                    insertNodeEnd(&newWord, inputLine[i]);
                }
                printf("Your word has been saved!\n");
                break;
            case 2:
                insertNodeEnd(&newWord, '\n');
                printf("New line has been added!\n");
                break;
            case 3:
                printf("Enter the file name for saving:\n");
                scanf("%s", fileName);
                printf("Name has been saved! \n");
            case 4:
                break;
            case 5:
                displayList(newWord);
                break;
            case 6:
                break;
            case 7:
                break;
            default:
                return 0;
        }
    }
    return 0;
}
