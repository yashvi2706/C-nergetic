#include "f_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void writeUserOnTempFile(char *name,char* pass){
    FILE *fp = fopen("tempUser.csv","w");
    fprintf(fp,"%s,%s",name,pass);
    fclose(fp);
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
    print_border(whitebold"*"end);
    f_string_format(1, orange"Welcome To The Login Page!\n"end);
    char s[100];
    date_d(s,sizeof(s));
    f_string_format(2, "%s        \n",s);
    print_border(whitebold"*"end);
}

void login() {
    FILE* fp = fopen("userCredentials.csv", "r");
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
                f_string_format(1, green"Login Successful!\n"end);
                writeUserOnTempFile(username,password);
                SLEEP(4);
                clear_console();
                flag = 0;
                break;
            }
            current = current->next;
        }
        if (flag) {
            f_string_format(1,red"Invalid username or password. Please try again.\n"end);
            SLEEP(4);
            clear_console();
            print_UI();
        }
    }
}

int main() {
    clear_console();
    login();
    return 0;
}
