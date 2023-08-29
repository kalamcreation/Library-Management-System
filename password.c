#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to save admin password to a file
void saveAdminPassword(const char *password) {
    FILE *file = fopen("admin_password.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    fprintf(file, "%s", password);
    fclose(file);
    printf("Admin password saved.\n");
}

// Function to check if entered admin password is correct
int isAdminPasswordCorrect(const char *enteredPassword, const char *adminPassword) {
    return strcmp(enteredPassword, adminPassword) == 0;
}

int main() {
    char adminPassword[100];
    char enteredPassword[100];
    int isAdminLoggedIn = 0;

    // Load admin password from file
    FILE *adminFile = fopen("admin_password.txt", "r");
    if (adminFile != NULL) {
        fscanf(adminFile, "%s", adminPassword);
        fclose(adminFile);
    }
else {
        // Initial admin password setup
        printf("Setting up initial admin password.\n");
        printf("Enter admin password: ");
        scanf("%s", adminPassword);
        saveAdminPassword(adminPassword);
    }
    int choice;

    do {
        if (!isAdminLoggedIn) {
            printf("Enter admin password: ");
            scanf("%s", enteredPassword);

            if (isAdminPasswordCorrect(enteredPassword, adminPassword)) {
                isAdminLoggedIn = 1;
                printf("Admin login successful.\n");


            } else {
                printf("Incorrect admin password. Try again or exit.\n");
            }
        } else {
            printf("\nLibrary Management System Menu:\n");
            printf("1. Set Admin Password\n");
            printf("2. Change Admin Password\n");
            printf("3. Logout\n");
            printf("4. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
               /* case 1:
                    printf("Enter new admin password: ");
                    scanf("%s", adminPassword);
                    saveAdminPassword(adminPassword);
                    break; */
                case 2:
                    printf("Enter current admin password: ");
                    scanf("%s", enteredPassword);
                    if (isAdminPasswordCorrect(enteredPassword, adminPassword)) {
                        printf("Enter new admin password: ");
                        scanf("%s", adminPassword);
                        saveAdminPassword(adminPassword);
                    } else {
                        printf("Incorrect password. Cannot change.\n");
                    }
                    break;
                case 3:
                    isAdminLoggedIn = 0;
                    printf("Logged out.\n");
                    break;
                case 4:
                    printf("Exiting...\n");
                    break;
                default:
                    printf("Invalid choice. Please enter a valid option.\n");
            }
        }
    } while (choice != 4);

    return 0;
}
