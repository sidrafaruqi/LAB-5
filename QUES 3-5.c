#include <stdio.h>
#include <stdlib.h>

// Define the structure for a student record
struct Student {
    int rollNumber;
    char name[50];
    float marks;
};

// Function prototypes
void addStudent(FILE *file);
void displayStudents(FILE *file);
void deleteStudent(FILE *file, int rollNumber);
void modifyStudent(FILE *file, int rollNumber);

int main() {
    FILE *file;
    int choice;

    file = fopen("students.txt", "a+"); // Open file in append and read/write mode

    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    do {
        // Display menu
        printf("\nStudent Database System\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Delete Student\n");
        printf("4. Modify Student\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(file);
                break;
            case 2:
                displayStudents(file);
                break;
            case 3:
                {
                    int rollNumber;
                    printf("Enter the roll number to delete: ");
                    scanf("%d", &rollNumber);
                    deleteStudent(file, rollNumber);
                }
                break;
            case 4:
                {
                    int rollNumber;
                    printf("Enter the roll number to modify: ");
                    scanf("%d", &rollNumber);
                    modifyStudent(file, rollNumber);
                }
                break;
            case 5:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 5);

    fclose(file);
    return 0;
}

void addStudent(FILE *file) {
    struct Student newStudent;

    printf("Enter Roll Number: ");
    scanf("%d", &newStudent.rollNumber);
    printf("Enter Name: ");
    scanf("%s", newStudent.name);
    printf("Enter Marks: ");
    scanf("%f", &newStudent.marks);

    fseek(file, 0, SEEK_END);
    fwrite(&newStudent, sizeof(struct Student), 1, file);

    printf("Student added successfully.\n");
}

void displayStudents(FILE *file) {
    rewind(file); // Move file pointer to the beginning

    struct Student currentStudent;

    printf("\nStudent Records:\n");
    printf("Roll Number\tName\t\tMarks\n");

    while (fread(&currentStudent, sizeof(struct Student), 1, file) == 1) {
        printf("%d\t\t%s\t\t%.2f\n", currentStudent.rollNumber, currentStudent.name, currentStudent.marks);
    }
}

void deleteStudent(FILE *file, int rollNumber) {
    FILE *tempFile;
    struct Student currentStudent;

    tempFile = fopen("temp.txt", "w");

    rewind(file);

    int found = 0; // Flag to indicate whether the student was found

    while (fread(&currentStudent, sizeof(struct Student), 1, file) == 1) {
        if (currentStudent.rollNumber != rollNumber) {
            fwrite(&currentStudent, sizeof(struct Student), 1, tempFile);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("students.txt");
    rename("temp.txt", "students.txt");

    // Reopen the file in append and read/write mode
    file = fopen("students.txt", "a+");

    if (found) {
        printf("Student deleted successfully.\n");
    } else {
        printf("Student with Roll Number %d not found.\n", rollNumber);
    }
}

void modifyStudent(FILE *file, int rollNumber) {
    FILE *tempFile;
    struct Student currentStudent;

    tempFile = fopen("temp.txt", "w");

    rewind(file);

    int found = 0; // Flag to indicate whether the student was found

    while (fread(&currentStudent, sizeof(struct Student), 1, file) == 1) {
        if (currentStudent.rollNumber == rollNumber) {
            found = 1;
            printf("Enter new Name: ");
            scanf("%s", currentStudent.name);
            printf("Enter new Marks: ");
            scanf("%f", &currentStudent.marks);
        }

        fwrite(&currentStudent, sizeof(struct Student), 1, tempFile);
    }

    fclose(file);
    fclose(tempFile);

    remove("students.txt");
    rename("temp.txt", "students.txt");

    // Reopen the file in append and read/write mode
    file = fopen("students.txt", "a+");

    if (found) {
        printf("Student modified successfully.\n");
    } else {
        printf("Student with Roll Number %d not found.\n", rollNumber);
    }
}
