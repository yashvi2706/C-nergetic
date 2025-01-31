#include <stdio.h>
#include "f_string.h"
#include <stdlib.h>// for atoi, atof
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#define SLEEP(seconds) Sleep((seconds) * 1000)
#else
#include <unistd.h>
#define SLEEP(seconds) sleep(seconds)
#endif

// Define the hotel structure
struct hotel {
    int index_in_city;
    char name[201];
    char city[51];
    int price_of_deluxe;
    int price_of_single;
    int price_of_villa;
    int price_of_luxury;
    float rating;
    char address[501];
    char description[1001];
};

int num_hot_city=0;
int num_hotels2;
char city_name[51]; 

void display_hotels_by_city(struct hotel *hotels, int num_hotels, int city_number,char *city_name) {
    num_hotels2=num_hotels;


    switch (city_number) {
    case 1: strncpy(city_name, "Mumbai", 50); break;
    case 2: strncpy(city_name, "Delhi", 50); break;
    case 3: strncpy(city_name, "Bangalore", 50); break;
    case 4: strncpy(city_name, "Kolkata", 50); break;
    case 5: strncpy(city_name, "Chennai", 50); break;
    case 6: strncpy(city_name, "Udaipur", 50); break;
    case 7: strncpy(city_name, "Ahmedabad", 50); break;
    case 8: strncpy(city_name, "Goa", 50); break;
    case 9: strncpy(city_name, "Manali", 50); break;
    case 10: strncpy(city_name, "Hyderabad", 50); break;
    default: printf("Invalid city number.\n"); return;
}


     printf("\nHotels in %s (City Number: %d):\n", city_name, city_number);
    for (int i = 0; i < num_hotels; i++) {
        if (strcmp(hotels[i].city, city_name) == 0) {
            printf("\nHotel #%d:\n", i + 1);
            printf("Index in city: %d\n", hotels[i].index_in_city);
            printf("Name: %s\n", hotels[i].name);
            printf("City: %s\n", hotels[i].city);
            printf("Price of deluxe room: %d\n", hotels[i].price_of_deluxe);
            printf("Price of single room: %d\n", hotels[i].price_of_single);
            printf("Price of villa: %d\n", hotels[i].price_of_villa);
            printf("Price of luxury room: %d\n", hotels[i].price_of_luxury);
            printf("Rating: ");rating_to_stars(hotels[i].rating);
            printf("Address: %s\n", hotels[i].address);
            printf("Description: %s\n", hotels[i].description);
            num_hot_city+=1;

        }
    }
}


 int main(){
     clear_console();
    int city_number;
    struct hotel hotels[100];

    FILE *fp = fopen("hotel_list.csv", "r");

    if (!fp) {
        printf("File does not exist.\n");
    } else {
        int n = 1024;
        char buffer[n];
        int row = 0;
        int column = 0;

        // Array of structures to store hotels (maximum of 100 hotels for simplicity)
        

        while (fgets(buffer, n, fp)) {
            struct hotel temp_hotel;
            column = 0;
            row++;
            if (row == 1) continue; // Skip header row

            // Split the line into values
            char *value = strtok(buffer, ",");
            while (value) {
                switch (column) {
                    case 0:
                        temp_hotel.index_in_city = atoi(value); // Convert to integer
                        break;
                    case 1:
                        strncpy(temp_hotel.name, value, 200);
                        temp_hotel.name[200] = '\0';
                        break;
                    case 2:
                        strncpy(temp_hotel.city, value, 50);
                        temp_hotel.city[50] = '\0';
                        break;
                    case 3:
                        temp_hotel.price_of_deluxe = atoi(value);
                        break;
                    case 4:
                        temp_hotel.price_of_single = atoi(value);
                        break;
                    case 5:
                        temp_hotel.price_of_villa = atoi(value);
                        break;
                    case 6:
                        temp_hotel.price_of_luxury = atoi(value);
                        break;
                    case 7:
                        temp_hotel.rating = atof(value); // Convert to float
                        break;
                    case 8:
                        strncpy(temp_hotel.address, value, 500);
                        temp_hotel.address[500] = '\0';
                        break;
                    case 9:
                        strncpy(temp_hotel.description, value, 1000);
                        temp_hotel.description[1000] = '\0';
                        break;
                }
                value = strtok(NULL, ","); // Get the next value
                column++;
            }

            // Store the current hotel structure in the array
            if (row - 2 < 100) { // Ensure it doesn't exceed array size
                hotels[row - 2] = temp_hotel;
            } else {
                printf("Exceeded maximum number of hotels (100).\n");
                break;
            }
        }

        fclose(fp);

int i=0;
    int city_index;
    while(1){
        clear_console();
   
    

        // Display menu
        f_string_format(1, "\033[1m==============\033[0m");
        f_string_format(1, "\033[38;5;208m          TRIVAGO   \033[0m");
        f_string_format(1, "\033[1m  ==============\033[0m\n");
        f_string_format(0, yellow" City List"end);
        f_string_format(0, yellow" 1. Mumbai"end);
        f_string_format(0, yellow" 2. Delhi"end);
        f_string_format(0, yellow" 3. Bangalore"end);
        f_string_format(0, yellow" 4. Kolkata"end);
        f_string_format(0, yellow" 5. Chennai"end);
        f_string_format(0, yellow" 6. Udaipur"end);
        f_string_format(0, yellow" 7. Ahmedabad"end);
        f_string_format(0, yellow" 8. Goa"end);
        f_string_format(0, yellow" 9. Manali"end);
        f_string_format(0, yellow" 10. Hyderabad"end);
        f_string_format(0, yellow" 11. Exit"end);
        f_string_format(1, yellow" ==============================\n"end);
        printf("Enter your choice of city by selecting the index number: ");
    
        scanf("%d", &city_number);
        getchar();
        printf("\n"); // Clear newline character from input 
   
    
        switch (city_number) {
            case 1: clear_console();display_hotels_by_city(hotels, row-1, 1,city_name); break;
        case 2:
                clear_console();display_hotels_by_city(hotels, row-1, 2,city_name); break;
            case 3: clear_console();display_hotels_by_city(hotels, row-1, 3,city_name); break;
            case 4: clear_console();display_hotels_by_city(hotels, row-1, 4,city_name); break;
            case 5: clear_console();display_hotels_by_city(hotels, row-1, 5,city_name); break;
            case 6: clear_console();display_hotels_by_city(hotels, row-1, 6,city_name); break;
            case 7: clear_console();display_hotels_by_city(hotels, row-1, 7,city_name); break;
            case 8: clear_console();display_hotels_by_city(hotels, row-1, 8,city_name); break;
            case 9: clear_console();display_hotels_by_city(hotels, row-1, 9,city_name); break;
            case 10: clear_console();display_hotels_by_city(hotels, row-1, 10,city_name); break;
            case 11: clear_console();printf("Exiting Hotel Page.Goodbye!👋\n");system("./login");break;
        default: printf("Enter right number.\n");break;
        
    }
    
    printf("Enter the hotel index(Enter 0 to go back.): ");
    scanf("%d",&city_index);
    getchar();
    if(city_index==0){printf("Going back to city selection...\n");
    SLEEP(2);
    continue;}
    if(city_index>num_hot_city){printf("Enter a valid hotel index\n");SLEEP(2);continue;}
    else if(city_index<num_hot_city){


    for (int i = 0; i < num_hotels2; i++) {
        if (hotels[i].index_in_city==city_index && strcmp(hotels[i].city, city_name) == 0) {
            FILE *fptr = fopen("customer_choice.csv", "w");
            fprintf(fptr,"%i,%s,%s,%d,%d,%d,%d,%s\n",i,hotels[i].name, hotels[i].city, hotels[i].price_of_single, hotels[i].price_of_deluxe,hotels[i].price_of_villa,hotels[i].price_of_luxury,hotels[i].address);
            fflush(fptr);
            fclose(fptr);
            printf("You have selected : %s,%s\n",hotels[i].name,hotels[i].city);
            SLEEP(4);
            system("./select_stuff");
        }
    }
}
    
     }}}