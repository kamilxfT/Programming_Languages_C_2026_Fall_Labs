/*
 * Name: Kamil
 * Surname: Guluzada
 * Student ID: 251ADB067
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Check for filename argument for the bonus part
    const char *filename = (argc > 1) ? argv[1] : "data.txt";

    // 1 & 2. Open a file for writing and check if it opened successfully
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error opening file for writing");
        return 1; // Exit with a non-zero code on error
    }

    // Print the required message to the console
    printf("Writing lines to %s...\n", filename);

    // Write at least two lines of text into the file
    fprintf(fp, "Hello, file I/O in C!\n");
    fprintf(fp, "This is another line.\n");

    // Close the file properly
    fclose(fp);

    // 4. Open the same file again for reading
    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file for reading");
        return 1;
    }

    printf("Reading contents:\n");

    char buffer[256];
    int lines_read = 0;

    // 5. Read the contents line by line and print to the console
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
        lines_read++; // Bonus: Count the lines read
    }

    // Close the file after reading
    fclose(fp);

    // Bonus: Print the total number of lines read
    printf("Lines read: %d\n", lines_read);

    return 0;
}