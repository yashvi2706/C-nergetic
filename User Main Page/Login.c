#include "../Code_Snippets/String_Alignment/f_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#define SLEEP(seconds) Sleep((seconds) * 1000)
#else
#include <unistd.h>
#define SLEEP(seconds) sleep(seconds)
#endif

typedef struct Customer{
    char username[51];
    char email[255];
    char password[31];
    struct Customer *next;
}Customer;

Customer* createCustomer(const char* username, const char* email, const char* password) {
    Customer* newCustomer = (Customer*) malloc (sizeof(Customer));

    strcpy(newCustomer->username, username);
    strcpy(newCustomer->email, email);
    strcpy(newCustomer->password, password);

    newCustomer->next = NULL;
    return newCustomer;
}

void appendCustomer(Customer** head, const char* username, const char* email, const char* password) {
    Customer* newCustomer = createCustomer(username, email, password);

    if (*head == NULL) {
        *head = newCustomer;
    } else {
        Customer* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newCustomer;
    }
}

void print_UI() {
    print_border("*");
    f_string_format(1, "Welcome To The Login Page!\n");
    char s[100];
    date_d(s,sizeof(s));
    f_string_format(2, "%s        \n",s);
    print_border("*");
}

void login() {
    FILE* fp = fopen("output.csv", "r");
    if (!fp) {
    printf("File does not exist.\n");
    return;
    }
    char buffer[1024];
    Customer* customerList = NULL;
    while (fgets(buffer, sizeof(buffer), fp)) {
        char* username = strtok(buffer, ",");
        char* email = strtok(NULL, ",");
        char* password = strtok(NULL, ",");
        password[strcspn(password, "\n")] = '\0'; // Remove trailing newline
        appendCustomer(&customerList, username, email, password); // Add to the linked list
    }
    fclose(fp);
    print_UI();
    
    int flag = 1;
    while (flag){
        char username[51];
        char password[31];
        printf("\n");
        printf("Enter your username: ");
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = '\0';
        printf("Enter your password: ");
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = '\0';
        Customer* current = customerList;
        while (current != NULL) {
            if (strcmp(current->username, username) == 0 && strcmp(current->password, password) == 0) {
                f_string_format(1, "Login Successful!");
                SLEEP(4);
                clear_console();
                flag = 0;
                break;
            }
            current = current->next;
        }
        if (flag) {
            f_string_format(1, "Invalid username or password. Please try again.");
            SLEEP(4);
            clear_console();
            print_UI();
        }
    }
}

int main() {
    printf("Hello\n");
    clear_console();
    login();
    return 0;
}
