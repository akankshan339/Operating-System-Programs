#include <stdio.h>
#include <string.h>
#define MAX 100
// Function to compare two files and print matching lines
void compareFiles(FILE *file1, FILE *file2) {
    char line1[MAX], line2[MAX];

    rewind(file1);
    rewind(file2);

    printf("\nMatching lines in both files:\n");
    while (fgets(line1, MAX, file1) != NULL) {
        rewind(file2); // Rewind file2 for every line of file1
        while (fgets(line2, MAX, file2) != NULL) {
            if (strcmp(line1, line2) == 0) {
                printf("%s", line1);
            }
        }
    }
}
int main() {
    FILE *myFile, *friendFile;
    char myDetails[MAX], friendDetails[MAX];
    // Open and write to "myDetails.txt"
    myFile = fopen("myDetails.txt", "w");
    if (myFile == NULL) {
        printf("Error opening file myDetails.txt\n");
        return 1;
    }
    printf("Enter your details (up to 100 characters): ");
    fgets(myDetails, MAX, stdin);
    fprintf(myFile, "%s", myDetails);
    fclose(myFile);

    // Open and write to "friendDetails.txt"
    friendFile = fopen("friendDetails.txt", "w");
    if (friendFile == NULL) {
        printf("Error opening file friendDetails.txt\n");
        return 1;
    }
    printf("Enter your friend's details (up to 100 characters): ");
    fgets(friendDetails, MAX, stdin);
    fprintf(friendFile, "%s", friendDetails);
    fclose(friendFile);
    // Reopen both files for reading
    myFile = fopen("myDetails.txt", "r");
    friendFile = fopen("friendDetails.txt", "r");
    if (myFile == NULL || friendFile == NULL) {
        printf("Error reopening the files for comparison.\n");
        return 1;
    }
    // Compare files and print matching lines
    compareFiles(myFile, friendFile);
    fclose(myFile);
    fclose(friendFile);
    return 0;
}
