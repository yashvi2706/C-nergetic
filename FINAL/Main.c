#include <stdio.h>
#include "f_string.h"
#include <stdlib.h>

#ifdef _WIN32
    #define Register "registration.exe"
    #define Admin "admin.exe"
    #define Login "login.exe"
    #define ViewPage "viewpage.exe"
    #define UserPage "userpage.exe"
    #define Selection "selection.exe"
    #define Billing "Billing.exe"

#else
    #define Register "./registration"
    #define Admin "./admin"
    #define Login "./login"
    #define ViewPage "./viewpage"
    #define UserPage "./userpage"
    #define Selection "./selection"
    #define Billing "./Billing"

#endif

#ifdef _WIN32
    #define status(status) (status)
#else
    #include <sys/wait.h>
    #define status(status) WEXITSTATUS(status)
#endif

void printMain(){
    print_border(whitebold"*"end);
    f_string_format(1, orange"Welcome to RoomLeloBhai.Com\n"end);
    char s[100];
    date_d(s,sizeof(s));
    f_string_format(2, "%s        \n",s);
    print_border(whitebold"*"end);
}

void printUser(){
    print_border(whitebold"*"end);
    f_string_format(1, orange"User Page\n"end);
    char s[100];
    date_d(s,sizeof(s));
    f_string_format(2, "%s        \n",s);
    print_border(whitebold"*"end);
}

int entry(){
    clear_console();
    while (1){
        printMain();
        printf("Login(L)\n");
        printf("Register(R)\n");
        printf("Admin(A)\n");
        printf("Exit(E)\n\n");
        printf("Enter your choice: ");
        char choice;
        scanf(" %c", &choice);
        getchar();
        printf("\n");

        if (choice == 'L' || choice == 'l') {
            system(Login);
            return 1;
        } else if (choice == 'R' || choice == 'r') {
            system(Register);
        } else if (choice == 'A' || choice == 'a') {
            system(Admin);
        } else if (choice == 'E' || choice == 'e') {
            printf("Thanks for visiting...\n");
            SLEEP(2);
            return 0;
        } else {
            printf(red"Invalid choice. Please try again.\n"end);
            SLEEP(2);
        }
        clear_console();
    }
}

int hotel(){
    clear_console();
    while(1){
        printUser();
        printf(yellow"1. Book a Hotel(B)\n"end);
        printf(yellow"2. View Booked Hotels(V)\n"end);
        printf(yellow"3. Exit(E)\n"end);

        char choice;
        scanf(" %c", &choice);
        getchar();
        printf("\n");

        if (choice == 'V' || choice == 'v') {
            system(ViewPage);
        } else if (choice == 'B' || choice == 'b') {
            int ret=system(UserPage);
            int exit_code=status(ret);
            if (exit_code == 1) {
                            return 0;
            }else{
                system(Selection);
                return 1;
            }
        } else if (choice == 'E' || choice == 'e') {
            return 0;
        } else {
            printf(red"Invalid choice. Please try again.\n"end);
            SLEEP(2);
        }
        clear_console();
    }
}

int main(void){
    while (1){
        if (entry() == 0){
            break;
        }
        else{
            hotel();
        }
    }
    clear_console();
    return 0;
}
