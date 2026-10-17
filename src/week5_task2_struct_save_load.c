/*
 * Name: Kamil
 * Surname: Guluzada
 * Student ID: 251ADB067
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Required struct definition
typedef struct {
    char name[50];
    int age;
    float gpa;
} Student;

// Required function signatures
int save_student(const Student *s, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        return -1; // Return -1 if the file cannot be opened
    }

    // Save data as one line: name age gpa
    fprintf(fp, "%s %d %.2f\n", s->name, s->age, s->gpa);
    
    fclose(fp);
    return 0; // Success
}

int load_student(const char *filename, Student *s) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return -1; // Return -1 if the file cannot be opened
    }

    // Use fscanf and check if exactly 3 fields are read
    // %49s ensures no buffer overflow for the name
    int fields_read = fscanf(fp, "%49s %d %f", s->name, &s->age, &s->gpa);
    
    fclose(fp);

    if (fields_read != 3) {
        return -1; // Return -1 if data cannot be read properly
    }
    
    return 0; // Success
}

int main() {
    Student original_student = {"Alice", 21, 3.75f};
    Student loaded_student;
    const char *filename = "student.txt";

    printf("Saving student to file...\n");
    if (save_student(&original_student, filename) != 0) {
        printf("Error saving student.\n");
        return 1;
    }

    printf("Loading student from file...\n");
    if (load_student(filename, &loaded_student) != 0) {
        printf("Error loading student.\n");
        return 1;
    }

    // Print exactly in the required format
    printf("Loaded student: %s, %d, GPA %.2f\n", 
           loaded_student.name, 
           loaded_student.age, 
           loaded_student.gpa);

    return 0;
}