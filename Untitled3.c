#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Admin password
const char initialAdminPassword[] = "admin123";
char adminPassword[100];

// Function to save admin password to a file
void saveAdminPasswordToFile(const char *password) {
    FILE *file = fopen("admin_password.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    fprintf(file, "%s", password);
    fclose(file);
    printf("Admin password saved to file.\n");
}

// Function to load admin password from a file
void loadAdminPasswordFromFile() {
    FILE *file = fopen("admin_password.txt", "r");
    if (file == NULL) {
        printf("Admin password file not found. Using default password.\n");
        strcpy(adminPassword, initialAdminPassword);
        return;
    }

    fscanf(file, "%s", adminPassword);
    fclose(file);
}

// Function to change admin password
void changeAdminPassword() {
    char newPassword[100];
    printf("Enter new admin password: ");
    scanf("%s", newPassword);

    char confirmPassword[100];
    printf("Confirm new admin password: ");
    scanf("%s", confirmPassword);

    if (strcmp(newPassword, confirmPassword) == 0) {
        strcpy(adminPassword, newPassword);
        saveAdminPasswordToFile(adminPassword);
        printf("Admin password changed successfully.\n");
    } else {
        printf("Passwords do not match. Password not changed.\n");
    }
}

int main() {
    loadAdminPasswordFromFile();

    int choice;

    do {
        printf("\nLibrary Management System Menu:\n");
        printf("1. Admin Password Set\n");
        printf("2. Change Admin Password\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter initial admin password: ");
                scanf("%s", adminPassword);
                saveAdminPasswordToFile(adminPassword);
                printf("Initial admin password set.\n");
                break;
            case 2:
                changeAdminPassword();
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 3);

    return 0;
}
