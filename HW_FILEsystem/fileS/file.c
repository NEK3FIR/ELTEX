#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
 
#define FILENAME "output.txt" 
#define STRING "String from file" 
 
int main() { 
    FILE *file; 
    char buffer[100]; 
    int length, i; 
 
    // Create and write to the file 
    file = fopen(FILENAME, "w"); 
    if (file == NULL) { 
        perror("Error opening file for writing"); 
        return EXIT_FAILURE; 
    } 
    fprintf(file, "%s", STRING); 
    fclose(file); 
 
    // Open the file for reading 
    file = fopen(FILENAME, "r"); 
    if (file == NULL) { 
        perror("Error opening file for reading"); 
        return EXIT_FAILURE; 
    } 
 
    // Read the string from the file 
    fgets(buffer, sizeof(buffer), file); 
    fclose(file); 
 
    // Find the length of the string 
    length = strlen(buffer); 
 
    // Print the string in reverse 
    printf("Reversed string: "); 
    for (i = length - 1; i >= 0; i--) { 
        putchar(buffer[i]); 
    } 
    printf("\n"); 
 
    return EXIT_SUCCESS; 
}
