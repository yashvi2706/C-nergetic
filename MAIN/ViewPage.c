#include "../Code_Snippets/String_Alignment/f_string.h"
#include <stdio.h>
#include<stdlib.h>
#include<string.h>



void remove_newline(char *str)
    {
        size_t len = strlen(str);
        if (len > 0 && str[len - 1] == '\n') 
        {
            str[len - 1] = '\0';
        }
    }
    

int main()
{  

    clear_console();

    Company_name();
    header("View Booking Details");
    
    char arr[100];
    date_d(arr,sizeof(arr));
    f_string_format(2,"%s",arr);
    print_border("\033[1m~\033[0m");

    printf("\n");
    f_string_format(1,"\t\033[1;38;2;0;200;0m    Booking Information\033[0m\n");

    print_border("=");

    char target_user[100], target_password[100];
    char line[1000];
    char username[100], password[100], city[100], hotel_name[100], address[100], check_indate[50], room_type[50];
    int nights, rooms, total_price;

    printf("Enter the username to search: ");
    fgets(target_user, sizeof(target_user), stdin);
    target_user[strcspn(target_user, "\n")] = '\0';


    printf("Enter the password: ");
    fgets(target_password, sizeof(target_password), stdin);
    target_password[strcspn(target_password, "\n")] = '\0';
    

    FILE *fview_details = fopen("user_booked_data.csv", "r");

    while (fgets(line, sizeof(line), fview_details))
    {
        line[strcspn(line, "\n")] = '\0';
    
        char *temp = strdup(line); // Copy the line for strtok
        char *token = strtok(temp, ",");

        if (token && strcmp(token, target_user) == 0) 
        {
            // If the username matches, check the password
            strcpy(username, token);
            strcpy(password, strtok(NULL, ","));
            
            if (strcmp(password, target_password) == 0) 
            {

                strcpy(city, strtok(NULL, ","));
                strcpy(hotel_name, strtok(NULL, ","));
                strcpy(address, strtok(NULL, ","));
                strcpy(check_indate, strtok(NULL, ","));
                nights = atoi(strtok(NULL, ","));
                rooms = atoi(strtok(NULL, ","));
                strcpy(room_type, strtok(NULL, ","));
                total_price = atoi(strtok(NULL, ","));

                f_string_format(1," City : %s\n ",city);
                f_string_format(1," Hotel Name : %s\n",hotel_name);
                f_string_format(1," Location : %s\n",address);
                f_string_format(1," CheckIn Date : %s \n",check_indate);
                f_string_format(1," Total Number of Nights : %i\n",nights);
                f_string_format(1," Number Of Rooms : %i\n",rooms);
                f_string_format(1," Type Of Room : %s\n",room_type);
                f_string_format(1," Total Payment : Rs.%i\n",total_price);
                f_string_format(1," Payment Status: Confirmed \n");
                print_border("=");

                
            }
        }
        free(temp);
    
    }
    fclose(fview_details);

    return 0;
}
