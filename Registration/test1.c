#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Define the structure for a linked list node
typedef struct Customer{
    char username[51];
    char email[255];
    char password[31];
    struct Customer *next;
}Customer;

Customer* create_new_customer(char* username,char* email,char* password){
    Customer* new_customer=(Customer*)malloc(sizeof(Customer));
    strncpy(new_customer->username,username,50);
    new_customer->username[50]='\0';
    strncpy(new_customer->email,email,254);
    new_customer->email[254]='\0';
    strncpy(new_customer->password,password,30);
    new_customer->password[30]='\0';
    new_customer->next=NULL;
    return new_customer;}

void add_to_list(Customer** head,char* username,char* email,char* password){
    Customer* new_customer=create_new_customer(username,email,password);
    if(*head==NULL){
        *head=new_customer;
    }
    else{
        Customer* temp=*head;
        while(temp->next!=NULL){
            temp=temp->next;
        }
        temp->next=new_customer;}
}

bool usernameExists(struct Customer *current, char username) {
    while (current != NULL) {
        if (strcmp(current->username, username) == 0) {  // Compare strings with strcmp
            return true;  // Username exists
        }
        current = current->next;
    }
    return false;
}


int main() {
    Customer* next_node=NULL;
    FILE* fp=fopen("C:\Users\Jos samuel biju\OneDrive\Desktop\C-nergetic\Registration\output.csv","r");

    if(!fp)
        printf("File does not exist\n.");
    else{
        int n=1024;
        char buffer[n];
        int row=0;
        int column=0;
        while(fgets(buffer,n,fp)){
            char username[51],email[255],password[31];
            column=0;
            row++;
            if(row==1)
                continue;
            char *value=strtok(buffer,", ");
            Customer* new_customer=(Customer*)malloc(sizeof(Customer));
            while(value){
                if(column==0){strncpy(username,value,50);
                    username[50]='\0';}
                if(column==1){strncpy(email,value,254);email[254]='\0';}
                if(column==2){strncpy(password,value,30);
                    password[30]='\0';}

                value= strtok(NULL,", ");
                column++;}
            add_to_list(&next_node,username,email,password);
            }
        }fclose(fp);
    Customer* temp = next_node;
        while (temp != NULL) {
            printf("Username: %s, Email: %s, Password: %s\n", temp->username, temp->email, temp->password);
            temp = temp->next;
        }



    //my code
    char username[50], email[100], password[50];

    while (1) {
        printf("Enter a username: ");
        scanf("%s", username);  // It's safer to use fgets in real applications

        if (usernameExists(next_node,username)) {
            printf("Username already exists. Please choose a different one.\n");
        } else {
            break;  // Username is valid, proceed to email
        }
    }

    printf("Enter your email: ");
    scanf("%s", email);

    printf("Enter your password: ");
    scanf("%s", password);  // Secure input handling recommended here too

    // Success message
    printf("Customer registered successfully!\n");
    printf("Username: %s\n", username);
    printf("Email: %s\n", email);
    printf("Password: %s\n", password);  // In a real application, don't print the password!

    //create a new instance of the customer struct (darell)

    //add the new struct to the end of the linked list (darell)

    // Free the allocated memory
    // free(first);
    // free(second);
    // free(third);

    return 0;
}
