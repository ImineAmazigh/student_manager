#include <stdio.h>
#include <string.h>
#define PROBATION_GPA 2.5
#define MAX_STUDENTS 100

typedef struct Student {
    int id;
    char name[50];
    int credits_completed;
    float gpa;
} Student;

Student higher_gpa(Student s1, Student s2);
void print_student_card(Student s1);
int enroll_student(Student registry[], int *count, int id, char name[], float gpa, int credits);
void display_all(Student registry[], int *count);
void search_by_name(Student registry[], int *count, const char name[]);
void drop_student(Student registry[], int *count, int index);
void sort_by_gpa(Student registry[], int *count);


int main() {
    Student registry[MAX_STUDENTS];
    int student_count = 0;
    int choice;
    int id, credits, index;
    float gpa;
    char name[50];

    do {
        printf("\n--- MENU ---\n");
        printf("1. Enroll Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student by Name\n");
        printf("4. Drop Student (by Index)\n");
        printf("5. Sort Registry by GPA\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Enter ID: ");
                scanf("%d", &id);
                getchar();
                printf("Enter Name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;
                printf("Enter GPA: ");
                scanf("%f", &gpa);
                printf("Enter Credits: ");
                scanf("%d", &credits);
                enroll_student(registry, &student_count, id, name, gpa, credits);
                break;
            case 2:
                display_all(registry, &student_count);
                break;
            case 3:
                printf("Enter name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;
                search_by_name(registry, &student_count, name);
                break;
            case 4:
                printf("Enter index to drop: ");
                scanf("%d", &index);
                if (index >= 0 && index < student_count) {
                    drop_student(registry, &student_count, index);
                }
                break;
            case 5:
                sort_by_gpa(registry, &student_count);
                break;
            case 6:
                printf("Exiting...\n");
                break;
        }
    } while (choice != 6);

    return 0;
}

Student higher_gpa(Student s1, Student s2) {
    if (s1.gpa > s2.gpa) 
    return s1;
    else return s2;
}
void print_student_card(Student s) {
    printf("Student ID: %d\n", s.id);
    printf("NAME: %s\n", s.name);
    printf("GPA: %.2f\n", s.gpa);
    printf("PROGRESS: %d\n", s.credits_completed);
}
int enroll_student(Student registry[], int *count, int id, char name[], float gpa, int credits){
    registry[*count].gpa = gpa;
    registry[*count].id = id;
    strcpy(registry[*count].name, name);
    registry[*count].credits_completed = credits;
    if (gpa < PROBATION_GPA)
        printf("Warning: GPA below %f -- student placed on academic probation.", PROBATION_GPA);
    (*count)++;
    return *count;
}
void display_all(Student registry[], int *count) {
    printf("#\t ID\t NAME\t GPA\t Credits\n");
    for (int i=0; i < (*count); i++) {
        printf("[%d]\t %d\t /", i, registry[i].id);
        int k=0;
        while (registry[i].name[k] != '\0') {
            printf("%c", registry[i].name[k]);
            k++;
        }
        printf("  /  GPA: %.2f", registry[i].gpa);
        printf("  /  Credits: %d", registry[i].credits_completed);
        if (registry[i].gpa < 2.0f) {
            printf("  PROBATION");
            printf("\n");
        }
    }
}
void search_by_name(Student registry[], int *count, const char name[])
{
    int i=0, k=0;

    while (i < *count)
    {
        if (strcmp(registry[i].name, name) == 0) {
            printf("[%d]\t /", k);

            while (registry[i].name[k] != '\0') {
                printf("%c", registry[i].name[k]);
                k++;
            }
            printf(" / GPA: %.2f", registry[i].gpa);
            printf(" / Credits: %d", registry[i].credits_completed);
        }
        i++;
    }
}
void drop_student(Student registry[], int *count, int index) {
    for (int i=index; i < *count - 1; i++) {
        registry[i] = registry[i + 1];
    }
    (*count)--;
}

//ascending order
//This sorting uses bubble sort
void sort_by_gpa(Student registry[], int *count) {
    for (int i=0; i < (*count)-1; i++) {
        for (int j=0; j < (*count)-1-i; j++) {
            if (registry[j].gpa < registry[j+1].gpa) {
                Student temp = registry[j];
                registry[j] = registry[j + 1];
                registry[j+1] = temp;
            }
        }
    }
}
