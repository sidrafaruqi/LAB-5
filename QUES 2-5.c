#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fptr;
    char myString[80];
    int i;

    // Writing to the file
    fptr = fopen("lab6.txt", "w");
    printf("Enter the text : ");
    gets(myString);
    if (fptr != NULL) {
        fputs(myString, fptr);
        printf("The string has been copied to the file\n");
        fclose(fptr);
    } else {
        printf("Unable to open the file\n");
        return 1;
    }

    // Appending to the file
    FILE *fptr1;
    fptr1 = fopen("lab6.txt", "a");
    if (fptr1 != NULL) {
        fprintf(fptr1, " Good Morning!");
        fclose(fptr1);
    } else {
        printf("Unable to open the file\n");
        return 1;
    }

    // Reading from the file and counting words
    FILE *fptr2;
    fptr2 = fopen("lab6.txt", "r");
    if (fptr2 != NULL) {
        printf("Content of the file:\n");

        int wordCount = 0;
        while (fscanf(fptr2, "%s", myString) == 1) {
            printf("%s ", myString);
            wordCount++;
        }

        printf("\nTotal number of words: %d\n", wordCount);

        fclose(fptr2);
    } else {
        printf("Unable to open the file\n");
        return 1;
    }

    return 0;
}
