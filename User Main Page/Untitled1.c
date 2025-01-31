#include <stdio.h>
#include <string.h>
#include <stdlib.h> // for atoi, atof

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

int num_hotels2;
int num_hot_city=0;
char *city_name;

// Function to display hotels by city number
void display_hotels_by_city(struct hotel *hotels,int num_hotels, int city_number) {
    num_hotels2=num_hotels;
    // Determine 
    the city name based on the city number
    switch (city_number) {
        case 1: city_name = "Mumbai"; break;
        case 2: city_name = "Delhi"; break;
        case 3: city_name = "Bangalore"; break;
        case 4: city_name = "Kolkata"; break;
        case 5: city_name = "Chennai"; break;
        case 6: city_name = "Udaipur"; break;
        case 7: city_name = "Ahmedabad"; break;
        case 8: city_name = "Goa"; break;
        case 9: city_name = "Manali"; break;
        case 10: city_name = "Hyderabad"; break;
        default: printf("Invalid city number.\n"); return;
    }

    // Display all hotels for the given city
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
            printf("Rating: %.1f\n", hotels[i].rating);
            printf("Address: %s\n", hotels[i].address);
            printf("Description: %s\n", hotels[i].description);
            num_hot_city+=1;
        }
    }
}

int main() {
    FILE *fp = fopen("hotel_list.csv", "r");

    if (!fp) {
        printf("File does not exist.\n");
    } else {
        int n = 1024;
        char buffer[n];
        int row = 0;
        int column = 0;

        // Array of structures to store hotels (maximum of 100 hotels for simplicity)
        struct hotel hotels[100];

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

        // Get a city number input from the user
        int city_number;
        printf("\nEnter the index in city of the hotel you are choosing: ");
        scanf("%d", &city_number);

        // Display hotels for the chosen city number
        display_hotels_by_city(hotels, row - 1, city_number);

    int city_index;
    printf("\nEnter the city index: ");
    scanf("%d",&city_index);
    for (int i = 0; i < num_hotels2; i++) {
        if (hotels[i].index_in_city==city_index && strcmp(hotels[i].city, city_name) == 0) {
            FILE *fptr = fopen("customer_choice.csv", "w");
            fprintf(fptr,"%s,%s,%d,%d,%d,%d,%s\n",hotels[i].name, hotels[i].city, hotels[i].price_of_single, hotels[i].price_of_deluxe,hotels[i].price_of_villa,hotels[i].price_of_luxury,hotels[i].address);
            fclose(fptr);
        }
    }

    }


    return 0;
}
