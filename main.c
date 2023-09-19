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
void insertStringAtPosition(Node** head, const char* str, int line, int index) {
    Node* current = *head;
    Node* prev = NULL;
    int currentLine = 0;
    int currentPosition = 0;

    while (current != NULL) {
        if (currentLine == line && currentPosition == index) {
            for (int i = 0; str[i] != '\0'; i++) {
                Node* newNode = createNode(str[i]);
                newNode->next = current;
                if (prev == NULL) {
                    *head = newNode;
                } else {
                    prev->next = newNode;
                }
                prev = newNode;
            }
            return; // Insertion complete
        }

        if (current->data == '\n') {
            currentLine++;
            currentPosition = 0;
        } else {
            currentPosition++;
        }

        prev = current;
        current = current->next;
    }

    // If the line or index is out of bounds, insert at the end
    for (int i = 0; str[i] != '\0'; i++) {
        Node* newNode = createNode(str[i]);
        if (prev != NULL) {
            prev->next = newNode;
        } else {
            *head = newNode;
        }
        prev = newNode;
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
        printf("Choose the command:\n");
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
                FILE *file = fopen(fileName, "w");
                if (file == NULL) {
                    printf("Failed to open the file for writing.\n");
                } else {
                    displayList(newWord);
                    Node* current = newWord;
                    while (current != NULL) {
                        fputc(current->data, file);
                        current = current->next;
                    }
                    fclose(file);
                    printf("Data has been saved to the file.\n");
                }
                break;
            case 4:
            {
                printf("Enter the file name to read:\n");
                scanf("%s", fileName);
                FILE* file = fopen(fileName, "r");

                if (file == NULL) {
                    printf("Failed to open the file for reading.\n");
                } else {
                    char ch;
                    while ((ch = fgetc(file)) != EOF) {
                        putchar(ch);
                    }
                    fclose(file);
                }
            }
                break;
            case 5:
                displayList(newWord);
                break;
            case 6:
            {
                int line, index;
                printf("Choose line and index: ");
                scanf("%d %d", &line, &index);
                printf("Enter text to insert: ");
                scanf(" %[^\n]s", inputLine);
                insertStringAtPosition(&newWord, inputLine, line, index);
                printf("Text has been inserted!\n");
            }
                break;
            case 7:
                break;
            default:
                // Free the linked list before exiting
                freeList(newWord);
                return 0;
        }
    }
    return 0;
}
