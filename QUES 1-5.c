#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fptr;
    char myString[80];
    int i;
    fptr=fopen("lab6.txt","w");
    printf("Enter the text : ");
    gets(myString);
    if(fptr!=NULL){
    fputs(myString,fptr);
    printf("The string has been copied to the file");}
    else{
    printf("Unable to open the file");}
    fclose(fptr);

    FILE *fptr1;
    fptr1 = fopen("lab6.txt", "a");
    if(fptr1!=NULL){
    fprintf(fptr1, " Good Morning!");}
    else{
    printf("Unable to open the file");}
    fclose(fptr1);

    FILE *fptr2;
    fptr2 = fopen("lab6.txt", "r");
    char myString1[100];
    fgets(myString1, 100, fptr2);
    printf("\n%s", myString1);
    fclose(fptr2);

    return 0;
}
