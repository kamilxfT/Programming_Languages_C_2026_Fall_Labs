/*
 * Name: Kamil
 * Surname: Guluzada
 * Student ID: 251ADB067
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100

// Student struct
typedef struct {
    char name[50];
    int id;
    float gpa;
} Student;

// Function signatures
int load_students(Student arr[], int max);
int save_students(const Student arr[], int count);
void add_student(Student arr[], int *count);
void list_students(const Student arr[], int count);

// Helper function to read a line safely
void read_line(char *buffer, int size) {
    if (fgets(buffer, size, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
    }
}

int main() {
    Student students[MAX_STUDENTS];
    int count = 0;
    int choice;

    count = load_students(students, MAX_STUDENTS);
    printf("Loaded %d student(s) from students.txt\n", count);

    while (1) {
        printf("\n=== Student Management System ===\n");
        printf("1. List students\n");
        printf("2. Add student\n");
        printf("3. Save and Exit\n");
        printf("Select an option: ");
        
        char choice_buf[10];
        read_line(choice_buf, sizeof(choice_buf));
        choice = atoi(choice_buf);

        if (choice == 1) {
            list_students(students, count);
        } else if (choice == 2) {
            add_student(students, &count);
        } else if (choice == 3) {
            save_students(students, count);
            printf("Data saved. Goodbye!\n");
            break;
        } else {
            printf("Invalid option. Please try again.\n");
        }
    }

    return 0;
}

int load_students(Student arr[], int max) {
    FILE *fp = fopen("students.txt", "r");
    if (fp == NULL) {
        return 0; // File doesn't exist (first run)
    }

    int count = 0;
    char line[256];

    while (fgets(line, sizeof(line), fp) != NULL && count < max) {
        if (line[0] == '\n' || line[0] == '\0') continue;

        // Parse: name,ID,GPA
        int parsed = sscanf(line, "%49[^,],%d,%f", arr[count].name, &arr[count].id, &arr[count].gpa);
        
        if (parsed == 3) {
            count++;
        }
    }

    fclose(fp);
    return count;
}

int save_students(const Student arr[], int count) {
    FILE *fp = fopen("students.txt", "w");
    if (fp == NULL) {
        printf("Error opening file for saving.\n");
        return -1;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s,%d,%.2f\n", arr[i].name, arr[i].id, arr[i].gpa);
    }

    fclose(fp);
    return 0;
}

void add_student(Student arr[], int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("Cannot add more students (limit reached).\n");
        return;
    }

    char name_buf[50];
    char id_buf[20];
    char gpa_buf[20];
    int id;
    float gpa;
    int valid = 1;

    printf("Enter name: ");
    read_line(name_buf, sizeof(name_buf));
    
    if (strlen(name_buf) == 0 || strchr(name_buf, ',') != NULL) {
        valid = 0;
    }

    printf("Enter ID: ");
    read_line(id_buf, sizeof(id_buf));
    if (sscanf(id_buf, "%d", &id) != 1) {
        valid = 0;
    }

    printf("Enter GPA: ");
    read_line(gpa_buf, sizeof(gpa_buf));
    if (sscanf(gpa_buf, "%f", &gpa) != 1 || gpa < 0.0f || gpa > 4.0f) {
        valid = 0;
    }

    if (!valid) {
        printf("Invalid input. Student not added.\n");
        return;
    }

    strcpy(arr[*count].name, name_buf);
    arr[*count].id = id;
    arr[*count].gpa = gpa;
    (*count)++;

    printf("Student added successfully!\n");
}

void list_students(const Student arr[], int count) {
    if (count == 0) {
        printf("No students found.\n");
        return;
    }

    printf("%-6s %-20s %-5s\n", "ID", "Name", "GPA");
    for (int i = 0; i < count; i++) {
        printf("%-6d %-20s %.2f\n", arr[i].id, arr[i].name, arr[i].gpa);
    }
}