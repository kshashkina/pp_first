#include <stdio.h>

int main() {
    int commandNumber;
    char newWord [100];
    char fileName [50];
    int i = 0;

    while (1){
        printf("Write your command:\n");
        scanf("%d", &commandNumber);
        switch (commandNumber) {
            case 1:
                printf("Enter text to append:\n");
                scanf("%s", newWord);
                printf("Your word have been saved!\n");
                break;
            case 2:
                while (newWord[i] != 0){
                    i++;
                }
                newWord[i] = '\r';
                printf("New line has been added!\n");
                break;
            case 3:
                printf("Enter the file name for saving:\n");
                scanf("%s", fileName);
                printf("Name has been saved! \n");
            case 4:
                break;
            case 5:
                printf("%s", newWord);
            case 6:
                break;
            case 7:
                break;
            default:
                break;
        }
    }
    return 0;
}
