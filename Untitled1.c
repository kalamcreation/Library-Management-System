#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100

// Structure to represent a book
struct Book {
    char title[100];
    char author[100];
    int isbn;
    int available;
};

struct Book library[MAX_BOOKS];
int numBooks = 0;

// Admin password
const char adminPassword[] = "admin123";

// Function to add a book to the library
void addBook() {
    if (numBooks < MAX_BOOKS) {
        printf("Enter book title: ");
        scanf("%s", library[numBooks].title);
        printf("Enter author: ");
        scanf("%s", library[numBooks].author);
        printf("Enter ISBN: ");
        scanf("%d", &library[numBooks].isbn);
        library[numBooks].available = 1;
        numBooks++;
        printf("Book added successfully!\n");
    } else {
        printf("Library is full. Cannot add more books.\n");
    }
}

// Function to search for a book by title
void searchBook() {
    char searchTitle[100];
    printf("Enter book title to search: ");
    scanf("%s", searchTitle);

    for (int i = 0; i < numBooks; i++) {
        if (strcmp(library[i].title, searchTitle) == 0) {
            printf("Book found:\nTitle: %s\nAuthor: %s\nISBN: %d\n",
                   library[i].title, library[i].author, library[i].isbn);
            return;
        }
    }
    printf("Book not found.\n");
}

// Function to display all books in the library
void displayAllBooks() {
    if (numBooks == 0) {
        printf("No books in the library.\n");
    } else {
        printf("List of books:\n");
        for (int i = 0; i < numBooks; i++) {
            printf("%d. %s by %s (ISBN: %d)\n", i + 1, library[i].title, library[i].author, library[i].isbn);
        }
    }
}

// Function to save library data to a file
void saveDataToFile() {
    FILE *file = fopen("library_data.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < numBooks; i++) {
        fprintf(file, "%s,%s,%d,%d\n", library[i].title, library[i].author, library[i].isbn, library[i].available);
    }

    fclose(file);
    printf("Data saved to file.\n");
}

// Function to change the admin password
void changeAdminPassword() {
    char newPassword[100];
    printf("Enter new admin password: ");
    scanf("%s", newPassword);

    FILE *file = fopen("admin_password.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    fprintf(file, "%s", newPassword);
    fclose(file);
    printf("Admin password changed.\n");
}

int main() {
    // Load admin password from file
    FILE *adminFile = fopen("admin_password.txt", "r");
    if (adminFile != NULL) {
        fscanf(adminFile, "%s", adminPassword);
        fclose(adminFile);
    }

    int choice;
    char enteredPassword[100];

    printf("Enter admin password: ");
    scanf("%s", enteredPassword);

    if (strcmp(enteredPassword, adminPassword) == 0) {
        printf("Admin login successful.\n");
        do {
            printf("\nLibrary Management System Menu:\n");
            printf("1. Add Book\n");
            printf("2. Search Book\n");
            printf("3. Display All Books\n");
            printf("4. Save Data to File\n");
            printf("5. Change Admin Password\n");
            printf("6. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    addBook();
                    break;
                case 2:
                    searchBook();
                    break;
                case 3:
                    displayAllBooks();
                    break;
                case 4:
                    saveDataToFile();
                    break;
                case 5:
                    changeAdminPassword();
                    break;
                case 6:
                    printf("Exiting...\n");
                    break;
                default:
                    printf("Invalid choice. Please enter a valid option.\n");
            }
        } while (choice != 6);
    } else {
        printf("Incorrect admin password. Exiting...\n");
    }

    return 0;
}
