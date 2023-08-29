#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a book
struct Book {
    char title[100];
    char author[100];
    int pages;
    float price;
};

// Function prototypes
void addBook(struct Book books[], int *numBooks);
void displayBooks(struct Book books[], int numBooks);
void saveDataToFile(struct Book books[], int numBooks);
void searchBook(struct Book books[], int numBooks);
void adminMenu();
void changeAdminPassword(char adminPassword[]);

int main() {
    char adminPassword[20] = "admin"; // Default admin password
    struct Book books[100]; // Array to store books
    int numBooks = 0; // Number of books in the array
    int choice;

    do {
        printf("\nLibrary Management System\n");
        printf("1. Add Book\n");
        printf("2. Display All Books\n");
        printf("3. Search Book\n");
        printf("4. Save Data to File\n");
        printf("5. Admin Menu\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook(books, &numBooks);
                break;
            case 2:
                displayBooks(books, numBooks);
                break;
            case 3:
                searchBook(books, numBooks);
                break;
            case 4:
                saveDataToFile(books, numBooks);
                break;
            case 5:
                adminMenu(adminPassword);
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}

void addBook(struct Book books[], int *numBooks) {
    if (*numBooks < 100) {
        printf("Enter book title: ");
        scanf(" %[^\n]", books[*numBooks].title);
        printf("Enter author name: ");
        scanf(" %[^\n]", books[*numBooks].author);
        printf("Enter total pages: ");
        scanf("%d", &books[*numBooks].pages);
        printf("Enter price: ");
        scanf("%f", &books[*numBooks].price);

        (*numBooks)++;
        printf("Book added successfully!\n");
    } else {
        printf("Maximum number of books reached.\n");
    }
}

void displayBooks(struct Book books[], int numBooks) {
    if (numBooks > 0) {
        printf("Books in the library:\n");
        for (int i = 0; i < numBooks; i++) {
            printf("Book %d:\n", i + 1);
            printf("Title: %s\n", books[i].title);
            printf("Author: %s\n", books[i].author);
            printf("Pages: %d\n", books[i].pages);
            printf("Price: %.2f\n\n", books[i].price);
        }
    } else {
        printf("No books available in the library.\n");
    }
}

void saveDataToFile(struct Book books[], int numBooks) {
    FILE *file = fopen("books.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < numBooks; i++) {
        fprintf(file, "%s;%s;%d;%.2f\n", books[i].title, books[i].author, books[i].pages, books[i].price);
    }

    fclose(file);
    printf("Data saved to file successfully.\n");
}

void searchBook(struct Book books[], int numBooks) {
    char searchTitle[100];
    printf("Enter book title to search: ");
    scanf(" %[^\n]", searchTitle);

    int found = 0;
    for (int i = 0; i < numBooks; i++) {
        if (strstr(books[i].title, searchTitle) != NULL) {
            printf("Book found:\n");
            printf("Title: %s\n", books[i].title);
            printf("Author: %s\n", books[i].author);
            printf("Pages: %d\n", books[i].pages);
            printf("Price: %.2f\n", books[i].price);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Book not found.\n");
    }
}

void adminMenu(char adminPassword[]) {
    char enteredPassword[20];
    printf("Enter admin password: ");
    scanf(" %[^\n]", enteredPassword);

    if (strcmp(adminPassword, enteredPassword) == 0) {
        int adminChoice;
        do {
            printf("\nAdmin Menu\n");
            printf("1. Change Admin Password\n");
            printf("2. Exit Admin Menu\n");
            printf("Enter your choice: ");
            scanf("%d", &adminChoice);

            switch (adminChoice) {
                case 1:
                    changeAdminPassword(adminPassword);
                    break;
                case 2:
                    printf("Exiting Admin Menu...\n");
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        } while (adminChoice != 2);
    } else {
        printf("Incorrect admin password.\n");
    }
}

void changeAdminPassword(char adminPassword[]) {
    printf("Enter new admin password: ");
    scanf(" %[^\n]", adminPassword);
    printf("Admin password changed successfully!\n");
}
