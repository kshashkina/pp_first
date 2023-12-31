#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

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
    // If the list is empty, make the new node the head of the list
    if (*head == NULL) {
        *head = newNode;
    } else {
        // Otherwise, traverse to the end of the list and insert the new node
        Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Function to insert a node at a specific position in the linked list
// Function to insert a string at a specific position in the linked list
void insertStringAtPosition(Node** head, const char* str, int line, int index) {
    Node* current = *head; // Start at the head of the list
    Node* prev = NULL;     // Pointer to the previous node
    int currentLine = 0;   // Current line number
    int currentPosition = 0; // Current position within the line

    // Traverse the list to find the specified line and index
    while (current != NULL) {
        if (currentLine == line && currentPosition == index) {
            // Insert the characters from the string into the list
            for (int i = 0; str[i] != '\0'; i++) {
                Node* newNode = createNode(str[i]);
                newNode->next = current;
                if (prev == NULL) {
                    *head = newNode; // Update the head if inserting at the beginning
                } else {
                    prev->next = newNode; // Update the previous node's next pointer
                }
                prev = newNode; // Update the previous node to the newly inserted node
            }
            return; // Insertion complete
        }

        if (current->data == '\n') {
            currentLine++; // Move to the next line
            currentPosition = 0; // Reset the position within the line
        } else {
            currentPosition++; // Move to the next character within the line
        }

        prev = current; // Update the previous node
        current = current->next; // Move to the next node
    }

    // If the line or index is out of bounds, insert at the end of the list
    for (int i = 0; str[i] != '\0'; i++) {
        Node* newNode = createNode(str[i]);
        if (prev != NULL) {
            prev->next = newNode;
        } else {
            *head = newNode; // Update the head if inserting at the beginning
        }
        prev = newNode; // Update the previous node
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

void CleanWithDelay(int seconds){
    Sleep(seconds*1000);
    system("cls");
};

int main() {
    int commandNumber;
    Node* newWord = NULL; // Initialize the linked list
    char inputLine[100]  = {'\0'};
    char fileName[50];

    while (1) {
        CleanWithDelay(2);
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
                    printf("\n");
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
            {
                printf("Enter the substring to search for:\n");
                scanf(" %[^\n]s", inputLine);

                Node* current = newWord;
                int lineIndex = 0;
                int line = 0;
                bool found = false;

                while (current != NULL) {
                    if (current->data == '\n') {
                        line++;
                        lineIndex = 0;
                        current = current -> next;
                    } else if (current->data == inputLine[0]) {
                        int inputIndex = 0;
                        while (current->data == inputLine[inputIndex]) {
                            current = current->next;
                            inputIndex++;
                            if (inputLine[inputIndex] == '\0') {
                                printf("Found at line %d and index %d\n", line, lineIndex);
                                found = true;
                                lineIndex += inputIndex;
                                break;
                            }
                        }
                    } else {
                        current = current->next;
                        lineIndex++;
                    }
                }

                if (!found) {
                    printf("Substring not found.\n");
                    break;
                }
                break;
            }
            default:
                // Free the linked list before exiting
                freeList(newWord);
                return 0;
        }
    }
}
