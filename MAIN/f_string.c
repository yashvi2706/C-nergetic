#include "f_string.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <sys/ioctl.h>
#endif

// Function to get the terminal width dynamically
static int get_terminal_width() {
    int width = 80; // Default width if detection fails

#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }
#else
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) {
        width = w.ws_col;
    }
#endif

    return width;
}

void print_border(char *border) {
    int width = get_terminal_width();
    for (int i = 0; i < width; i++) {
        printf("%s", border);
    }
    printf("\n");
}

void Company_name() 
{
    print_border("\033[1m~\033[0m");
    printf("\n");
    f_string_format(0,"\033[1;38;2;255;165;0mRoom.Lelo.Bhai.com\033[0m");
    printf("\n");
    char arr[100];
    date_d(arr,sizeof(arr));
    f_string_format(2,"%s",arr);
    print_border("\033[1m~\033[0m");
    printf("\n");
}

void header(char ar[100])
{
    f_string_format(1,"\t\033[1;38;2;0;200;0m\t%s\033[0m\n",ar);
    print_border("-");
    print_border("-");
}

void footer()
{
    printf("\n");
    print_border("-");
    f_string_format(1,"Customer Care :98989XXXXX");
    printf("\n");
    f_string_format(1,"email id :temp@gmail.com");
    printf("\n");
    f_string_format(1,"CompanyName | (C) ");
}

// Function to format and print a string with alignment
void f_string_format(int align, const char* format, ...) {
    int width = get_terminal_width(); // Get dynamic terminal width
    char buffer[1024];

    // Format the string
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    int len = strlen(buffer); // Length of the formatted string
    int padding = width - len; // Calculate padding for right alignment

    if (align == 1) { // Center alignment
        int center_padding = padding / 2;
        if (center_padding > 0) {
            printf("%*s%s", center_padding, "", buffer);
        } else {
            printf("%s", buffer); // If the string is too wide
        }
    } else if (align == 2) { // Right alignment
        if (padding > 0) {
            printf("%*s", width, buffer);
        } else {
            printf("%s", buffer); // If the string is too wide
        }
    } else { // Left alignment
        printf("%s", buffer);
    }
}

int confirm_payment_fun()
{   
    f_string_format(1,"\b\bConfirm the Payment?(Y/N):");
    char confirm_payment_in_fun;
    
    scanf(" %c",&confirm_payment_in_fun);
    while (getchar() != '\n');
    printf("\n");
    if(confirm_payment_in_fun=='Y' || confirm_payment_in_fun=='y')
    {   
        f_string_format(1,"Payment is confirmed");
        printf("\n");
        return 1;
    }
    else if(confirm_payment_in_fun=='N' || confirm_payment_in_fun=='n')
    {   f_string_format(1,"Are you sure? Please enter Y or N:");

        
        scanf(" %c",&confirm_payment_in_fun);
        while (getchar() != '\n');
        
        printf("\n");
        if(confirm_payment_in_fun=='Y' || confirm_payment_in_fun=='y')
        {    
            f_string_format(1,"Sure,Payment is declined!");
            printf("\n");
            return 0;
        }
        else if(confirm_payment_in_fun=='N' || confirm_payment_in_fun=='n')
        {   f_string_format(1,"OK,Confirming the Payment....");
            printf("\n");
            return 1;
        }
        else
        {
            f_string_format(1,"Invalid Input,Due to which Payment is declined");
            printf("\n");
            return 0;
        }
    }
    else
    {
        f_string_format(1,"Invalid Input");
        printf("\n");
        f_string_format(1,"You want to continue and Confirm the Payment? Please enter Y or N:");
        
        scanf(" %c",&confirm_payment_in_fun);
        while (getchar() != '\n');
        
        printf("\n");
        if(confirm_payment_in_fun=='Y' || confirm_payment_in_fun=='y')
        {    
            f_string_format(1,"Ok,Confirming the Payment....");
            printf("\n");
            return 1;
        }
        else if(confirm_payment_in_fun=='N' || confirm_payment_in_fun=='n')
        {   
            f_string_format(1,"Sure,Payment is declined!");
            printf("\n");
            return 0;
        }
        else
        {
            f_string_format(1,"Invalid Input,Due to which Payment is declined");
            printf("\n");
            return 0;
        }
    }


}

// Function to clear the console
void clear_console() {
#ifdef _WIN32
    // Windows
    system("cls");
#else
    // Linux or macOS
    system("clear");
#endif
}

void date_d(char* buffer, size_t buffer_size) {
    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);

    // Get the day with suffix (st/nd/rd/th)
    int day = tm_info->tm_mday;
    char suffix[3];
    if (day >= 11 && day <= 13) {
        strcpy(suffix, "th");
    } else {
        switch (day % 10) {
            case 1: strcpy(suffix, "st"); break;
            case 2: strcpy(suffix, "nd"); break;
            case 3: strcpy(suffix, "rd"); break;
            default: strcpy(suffix, "th"); break;
        }
    }

    // Format the date (e.g., "23rd, June 2024")
    strftime(buffer, buffer_size, "%d", tm_info); // Get the day
    strcat(buffer, suffix);  // Add the suffix (st/nd/rd/th)
    strftime(buffer + strlen(buffer), buffer_size - strlen(buffer), ", %B %Y", tm_info); // Add the month and year

    // Add Time in 12-hour format with AM/PM
    char time_str[10];
    strftime(time_str, sizeof(time_str), " %I:%M %p", tm_info);  // Hour and Minute with AM/PM
    strcat(buffer, time_str);
}