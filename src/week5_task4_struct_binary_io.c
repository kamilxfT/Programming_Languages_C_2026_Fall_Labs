/*
 * Name: Kamil
 * Surname: Guluzada
 * Student ID: 251ADB067
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Same Student struct as Task 2
typedef struct {
    char name[50];
    int age;
    float gpa;
} Student;

// Required function signatures
int save_student_binary(const Student *s, const char *filename) {
    FILE *fp = fopen(filename, "wb"); // "wb" for write binary
    if (fp == NULL) {
        return -1;
    }
    
    // fwrite returns number of elements written
    if (fwrite(s, sizeof(Student), 1, fp) != 1) {
        fclose(fp);
        return -1;
    }
    
    fclose(fp);
    return 0;
}

int load_student_binary(const char *filename, Student *s) {
    FILE *fp = fopen(filename, "rb"); // "rb" for read binary
    if (fp == NULL) {
        return -1;
    }
    
    // fread returns number of elements read
    if (fread(s, sizeof(Student), 1, fp) != 1) {
        fclose(fp);
        return -1;
    }
    
    fclose(fp);
    return 0;
}

long file_size(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        return -1;
    }
    
    // Move pointer to the end of the file
    fseek(fp, 0, SEEK_END);
    // Get the current position (which is the size)
    long size = ftell(fp);
    
    fclose(fp);
    return size;
}

int main() {
    // Zero-initialize the struct to avoid writing garbage memory to disk
    Student original = {"Alice", 21, 3.75f};
    Student loaded;
    const char *bin_filename = "student.bin";
    const char *txt_filename = "student.txt";

    printf("Saving student in binary format...\n");
    if (save_student_binary(&original, bin_filename) != 0) {
        printf("Error saving binary file.\n");
        return 1;
    }

    printf("Loading student from binary file...\n");
    if (load_student_binary(bin_filename, &loaded) != 0) {
        printf("Error loading binary file.\n");
        return 1;
    }

    printf("Loaded student: %s, %d, GPA %.2f\n", loaded.name, loaded.age, loaded.gpa);

    // Also save the same record in text format to compare sizes
    FILE *fp = fopen(txt_filename, "w");
    if (fp != NULL) {
        fprintf(fp, "%s %d %.2f\n", original.name, original.age, original.gpa);
        fclose(fp);
    }

    // Get the sizes
    long txt_size = file_size(txt_filename);
    long bin_size = file_size(bin_filename);

    printf("Text file size: %ld bytes\n", txt_size);
    printf("Binary file size: %ld bytes\n", bin_size);

    return 0;
}