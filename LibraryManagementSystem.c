#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a book
struct Book
{
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
//void deleteBook(struct Book books[], int *numBooks);
void adminMenu();
// Function to save admin password to a file
void saveAdminPassword(const char *password)
{
    FILE *file = fopen("admin_password.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    fprintf(file, "%s", password);
    fclose(file);
    printf("Admin password saved.\n");
}

// Function to check if entered admin password is correct
int isAdminPasswordCorrect(const char *enteredPassword, const char *adminPassword)
{
    return strcmp(enteredPassword, adminPassword) == 0;
}

int main()
{
    char adminPassword[100];
    char enteredPassword[100];
    int isAdminLoggedIn = 0;
    printf("\t\t **** Library Management System ****\n\n");
    // Load admin password from file
    FILE *adminFile = fopen("admin_password.txt", "r");
    if (adminFile != NULL)
    {
        fscanf(adminFile, "%s", adminPassword);
        fclose(adminFile);
    }
    else
    {
        // Initial admin password setup
        printf("Setting up initial admin password.\n");
        printf("Enter admin password: ");
        scanf("%s", adminPassword);
        saveAdminPassword(adminPassword);
    }



    struct Book books[100]; // Array to store books
    int numBooks = 0; // Number of books in the array

// Load existing data from file
    FILE *file = fopen("books.txt", "r");
    if (file != NULL)
    {
        while (!feof(file) && numBooks < 100)
        {
            if (fscanf(file, " %[^;];%[^;];%d;%f\n", books[numBooks].title, books[numBooks].author, &books[numBooks].pages, &books[numBooks].price) == 4)
            {
                numBooks++;
            }
        }
        fclose(file);
    }


    int choice;

    do
    {
        if (!isAdminLoggedIn)
        {
            printf("Enter admin password: ");
            scanf("%s", enteredPassword);

            if (isAdminPasswordCorrect(enteredPassword, adminPassword))
            {
                isAdminLoggedIn = 1;
                printf("Admin login successful.\n");


            }
            else
            {
                printf("Incorrect admin password. Try again or exit.\n");
            }
        }
        else
        {

            printf("\nLibrary Management System\n");
            printf("1. Add Book\n");
            printf("2. Save Data to File\n");
            printf("3. Search Book\n");
            printf("4. Delete Book \n");
            printf("5. Display All Books\n");

            //  printf("5. Change Admin Password\n");
            printf("6. Change Admin Password\n");
            printf("7. Logout\n");
            printf("8. Exit\n");
            printf("--------------------------------\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice)
            {
            case 1:
                printf("--------------------------------\n\n");
                addBook(books, &numBooks);
                break;
            case 2:
                saveDataToFile(books, numBooks);
                break;

            case 3:
                printf("--------------------------------\n\n");
                searchBook(books, numBooks);
                break;

            case 4:

                printf("--------------------------------\n\n");
                int bookIndex;
                printf("Enter the index of the book to delete: ");
                scanf("%d", &bookIndex);
                bookIndex=bookIndex-1;
                if (bookIndex >= 0 && bookIndex < numBooks)
                {
                    deleteBook(books, &numBooks, bookIndex);
                }
                else
                {
                    printf("Invalid index. No book deleted.\n");
                }
                break;

            case 5:
                printf("--------------------------------\n\n");
                displayBooks(books, numBooks);
                break;
            case 6:

                printf("Enter current admin password: ");
                scanf("%s", enteredPassword);
                if (isAdminPasswordCorrect(enteredPassword, adminPassword))
                {
                    printf("Enter new admin password: ");
                    scanf("%s", adminPassword);
                    saveAdminPassword(adminPassword);
                }
                else
                {
                    printf("Incorrect password. Cannot change.\n");
                }
                break;

            case 7:
                isAdminLoggedIn = 0;
                printf("Logged out.\n");
                break;


            case 8:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
            }
        }
    }
    while (choice != 8);

    return 0;
}

void addBook(struct Book books[], int *numBooks)
{
    if (*numBooks < 100)
    {
        printf("\t\t **** Add New book ****\n\n");
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
    }
    else
    {
        printf("Maximum number of books reached.\n");
    }
}

void displayBooks(struct Book books[], int numBooks)
{
    if (numBooks > 0)
    {

        printf("Books in the library:\n");
        for (int i = 0; i < numBooks; i++)
        {
            printf("Book %d:\n", i + 1);
            printf("\t");
            printf("Title: %s\n", books[i].title);
            printf("\t");
            printf("Author: %s\n", books[i].author);
            printf("\t");
            printf("Pages: %d\n", books[i].pages);
            printf("\t");
            printf("Price: %.2f Tk.\n\n", books[i].price);
        }
    }
    else
    {
        printf("No books available in the library.\n");
    }

}

void saveDataToFile(struct Book books[], int numBooks)
{
    FILE *file = fopen("books.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < numBooks; i++)
    {
        fprintf(file, "%s;%s;%d;%.2f\n", books[i].title, books[i].author, books[i].pages, books[i].price);
    }

    fclose(file);
    printf("Book saved to file successfully.\n");

}

void searchBook(struct Book books[], int numBooks)
{
    printf("\t\t **** Now Searching your book ****\n\n");
    char searchTitle[100];
    printf("Enter book title to search: ");
    scanf(" %[^\n]", searchTitle);

    int found = 0;
    for (int i = 0; i < numBooks; i++)
    {
        if (strstr(books[i].title, searchTitle) != NULL)
        {
            printf("Book found:\n");
            printf("\t");
            printf("Title: %s\n", books[i].title);
             printf("\t");
            printf("Author: %s\n", books[i].author);
             printf("\t");
            printf("Pages: %d\n", books[i].pages);
             printf("\t");
            printf("Price: %.2f Tk\n", books[i].price);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Book not found.\n");
    }
}
void deleteBook(struct Book books[], int *numBooks, int indexToDelete)
{
    if (indexToDelete >= 0 && indexToDelete < *numBooks)
    {
        for (int i = indexToDelete; i < *numBooks - 1; i++)
        {
            books[i] = books[i + 1];
        }
        (*numBooks)--;
        printf("Book deleted successfully!\n");
    }
    else
    {
        printf("Invalid index. No book deleted.\n");
    }
}
