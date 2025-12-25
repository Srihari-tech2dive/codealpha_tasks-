#include <stdio.h>
#include <stdlib.h>

struct student {
    int roll;
    char name[30];
    float marks;
};

void addStudent() {
    FILE *fp = fopen("students.dat", "ab");
    struct student s;

    printf("Enter Roll No: ");
    scanf("%d", &s.roll);
    printf("Enter Name: ");
    scanf("%s", s.name);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
}

void displayStudents() {
    FILE *fp = fopen("students.dat", "rb");
    struct student s;

    while(fread(&s, sizeof(s), 1, fp))
        printf("\nRoll: %d  Name: %s  Marks: %.2f", s.roll, s.name, s.marks);

    fclose(fp);
}

void searchStudent() {
    FILE *fp = fopen("students.dat", "rb");
    struct student s;
    int roll, found = 0;

    printf("Enter Roll No to search: ");
    scanf("%d", &roll);

    while(fread(&s, sizeof(s), 1, fp)) {
        if(s.roll == roll) {
            printf("\nFound: %s %.2f", s.name, s.marks);
            found = 1;
            break;
        }
    }
    if(!found)
        printf("Student not found");

    fclose(fp);
}

int main() {
    int choice;

    do {
        printf("\n\n1.Add\n2.Display\n3.Search\n4.Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
        }
    } while(choice != 4);

    return 0;
}
