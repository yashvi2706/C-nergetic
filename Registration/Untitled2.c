#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Book {
    int bookNo;
    char bookName[50];
    char authorName[50];
    float price;
    int issued;
    struct Book *next;
} Book;

typedef struct {
    int rollNo;
    char studentName[50];
} Student;

void addBook(Book **head);
void showBooks(const Book *head);
void printBooksByAuthor(const Book *head, const char *authorName);
void checkBookAvailability(const Book *head, int bookNo);
void issueBook(Book *head, Student *student, int bookNo);
void saveLibraryToCSV(const Book *head);
void loadLibraryFromCSV(Book **head);
void freeLibrary(Book *head);

int main() {
    Book *library = NULL;
    Student student;
    int choice, bookNo;
    char authorName[50];

    loadLibraryFromCSV(&library);

    while (1) {
        printf("\n=== Library Management System ===\n");
        printf("1. Add a Book\n");
        printf("2. Show Books\n");
        printf("3. Print Books by Author\n");
        printf("4. Check Book Availability\n");
        printf("5. Issue a Book\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook(&library);
                break;
            case 2:
                showBooks(library);
                break;
            case 3:
                printf("Enter Author Name: ");
                getchar();
                fgets(authorName, sizeof(authorName), stdin);
                authorName[strcspn(authorName, "\n")] = '\0';
                printBooksByAuthor(library, authorName);
                break;
            case 4:
                printf("Enter Book Number to Check: ");
                scanf("%d", &bookNo);
                checkBookAvailability(library, bookNo);
                break;
            case 5:
                printf("Enter Student Roll Number: ");
                scanf("%d", &student.rollNo);
                printf("Enter Student Name: ");
                getchar();
                fgets(student.studentName, sizeof(student.studentName), stdin);
                student.studentName[strcspn(student.studentName, "\n")] = '\0';
                printf("Enter Book Number to Issue: ");
                scanf("%d", &bookNo);
                issueBook(library, &student, bookNo);
                break;
            case 6:
                saveLibraryToCSV(library);
                freeLibrary(library);
                printf("Data saved. Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}

void addBook(Book **head) {
    Book *newBook = (Book *)malloc(sizeof(Book));
    if (!newBook) {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("Enter Book Number: ");
    scanf("%d", &newBook->bookNo);
    printf("Enter Book Name: ");
    getchar();
    fgets(newBook->bookName, sizeof(newBook->bookName), stdin);
    newBook->bookName[strcspn(newBook->bookName, "\n")] = '\0';
    printf("Enter Author Name: ");
    fgets(newBook->authorName, sizeof(newBook->authorName), stdin);
    newBook->authorName[strcspn(newBook->authorName, "\n")] = '\0';
    printf("Enter Book Price: ");
    scanf("%f", &newBook->price);
    newBook->issued = 0;
    newBook->next = *head;
    *head = newBook;

    printf("Book added successfully.\n");
}

void showBooks(const Book *head) {
    if (!head) {
        printf("No books in the library.\n");
        return;
    }

    printf("\n=== Book List ===\n");
    while (head) {
        printf("Book No: %d\n", head->bookNo);
        printf("Book Name: %s\n", head->bookName);
        printf("Author: %s\n", head->authorName);
        printf("Price: %.2f\n", head->price);
        printf("Status: %s\n", head->issued ? "Issued" : "Available");
        printf("--------------------\n");
        head = head->next;
    }
}

void printBooksByAuthor(const Book *head, const char *authorName) {
    int found = 0;
    while (head) {
        if (strcmp(head->authorName, authorName) == 0) {
            printf("Book No: %d\n", head->bookNo);
            printf("Book Name: %s\n", head->bookName);
            printf("Price: %.2f\n", head->price);
            printf("--------------------\n");
            found = 1;
        }
        head = head->next;
    }
    if (!found) {
        printf("No books found by author %s.\n", authorName);
    }
}

void checkBookAvailability(const Book *head, int bookNo) {
    while (head) {
        if (head->bookNo == bookNo) {
            printf("Book %s is %s.\n", head->bookName, head->issued ? "Issued" : "Available");
            return;
        }
        head = head->next;
    }
    printf("Book not found.\n");
}

void issueBook(Book *head, Student *student, int bookNo) {
    while (head) {
        if (head->bookNo == bookNo) {
            if (head->issued) {
                printf("Book is already issued.\n");
                return;
            }
            head->issued = 1;
            printf("Book '%s' issued to %s (Roll No: %d).\n", head->bookName, student->studentName, student->rollNo);
            return;
        }
        head = head->next;
    }
    printf("Book not found.\n");
}

void saveLibraryToCSV(const Book *head) {
    FILE *file = fopen("library.csv", "w");
    if (!file) {
        printf("Error saving data to CSV.\n");
        return;
    }

    fprintf(file, "BookNo,BookName,AuthorName,Price,issued\n");

    while (head) {
        fprintf(file, "%d,%s,%s,%.2f,%d\n", head->bookNo, head->bookName, head->authorName, head->price, head->issued);
        head = head->next;
    }
    fclose(file);
    printf("Library data saved to library.csv.\n");
}

void loadLibraryFromCSV(Book **head) {
    FILE *file = fopen("library.csv", "r");
    if (!file) {
        printf("No previous data found. Starting fresh.\n");
        return;
    }

    char line[200];
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        Book *newBook = (Book *)malloc(sizeof(Book));
        if (!newBook) {
            printf("Memory allocation failed.\n");
            fclose(file);
            return;
        }

        char *token;
token = strtok(line, ",");
if (token) newBook->bookNo = atoi(token);

token = strtok(NULL, ",");
if (token) strncpy(newBook->bookName, token, sizeof(newBook->bookName) - 1);

token = strtok(NULL, ",");
if (token) strncpy(newBook->authorName, token, sizeof(newBook->authorName) - 1);

token = strtok(NULL, ",");
if (token) newBook->price = atof(token);

token = strtok(NULL, ",");
if (token) newBook->issued = atoi(token);


        newBook->next = *head;
        *head = newBook;
    }
    fclose(file);
    printf("Library data loaded from library.csv.\n");
}

void freeLibrary(Book *head) {
    while (head) {
        Book *temp = head;
        head = head->next;
        free(temp);
    }
}
