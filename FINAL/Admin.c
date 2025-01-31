#include "f_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Hotel{
    int index;
    char name[100];
    char city[100];
    int price_of_deluxe;
    int price_of_single;
    int price_of_villa;
    int price_of_luxury;
    float rating;
    char address[500];
    char description[1000];
    struct Hotel *next;
}Hotel;

void print_UI() {
    print_border(whitebold"*"end);
    f_string_format(1, orange"Welcome To The Admin Page!\n"end);
    char s[100];
    date_d(s,sizeof(s));
    f_string_format(2, "%s        \n",s);
    print_border(whitebold"*"end);
}

void freeMemory(Hotel* head) {
    Hotel* current = head;
    Hotel* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

void writeHotelWithHeaders(Hotel* head) {
    FILE* fp = fopen("hotelList.csv", "w");
    if (!fp) {
        printf("File does not exist.\n");
        return;
    }

    // Write the headers
    fprintf(fp, "index,hotel_name,city,deluxe_room_price,single_room_price,villa_price,luxury_price,rating,location,description\n");

    Hotel* current = head;
    while (current != NULL) {
        fprintf(fp, "%d,%s,%s,%d,%d,%d,%d,%.2f,%s,%s\n", current->index, current->name, current->city, current->price_of_deluxe, current->price_of_single, current->price_of_villa, current->price_of_luxury, current->rating, current->address, current->description);
        current = current->next;
    }

    fclose(fp);
}

Hotel* createHotel(int index, const char* name, char *city, int price_of_deluxe, int price_of_single, int price_of_villa, int price_of_luxury, float rating, const char* address, const char* description) {
    Hotel *newHotel = (Hotel*) malloc (sizeof(Hotel));

    newHotel->index = index;
    strcpy(newHotel->name, name);
    strcpy(newHotel->city, city);
    newHotel->price_of_deluxe = price_of_deluxe;
    newHotel->price_of_single = price_of_single;
    newHotel->price_of_villa = price_of_villa;
    newHotel->price_of_luxury = price_of_luxury;
    newHotel->rating = rating;
    strcpy(newHotel->address, address);
    strcpy(newHotel->description, description);

    newHotel->next = NULL;
    return newHotel;
}

void appendHotel(Hotel** head, int index, const char* name, char *city, int price_of_deluxe, int price_of_single, int price_of_villa, int price_of_luxury, float rating, const char* address, const char* description) {
    Hotel* newHotel = createHotel(index, name, city, price_of_deluxe, price_of_single, price_of_villa, price_of_luxury, rating, address, description);

    if (*head == NULL) {
        *head = newHotel;
    } else {
        Hotel* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newHotel;
    }
}

int getNextIndex(Hotel* head, char *city) {
    int maxIndex = 0;
    Hotel* current = head;
    while (current != NULL) {
        if (strcmp(current->city, city) == 0 && current->index > maxIndex) {
            maxIndex = current->index;
        }
        current = current->next;
    }
    return maxIndex + 1;
}

void addHotel(Hotel** head) {
    int  price_of_deluxe, price_of_single, price_of_villa, price_of_luxury;
    float rating;
    char name[100], address[500], description[1000],city[100];

    printf("Enter city                       : ");
    scanf("%99[^\n]", city);
    getchar();
    int index = getNextIndex(*head, city);
    printf("Enter name                 : ");
    scanf("%99[^\n]", name);
    printf("Enter price of deluxe room : ");
    scanf("%d", &price_of_deluxe);
    printf("Enter price of single room : ");
    scanf("%d", &price_of_single);
    printf("Enter price of villa room  : ");
    scanf("%d", &price_of_villa);
    printf("Enter price of luxury room : ");
    scanf("%d", &price_of_luxury);
    printf("Enter rating               : ");
    scanf("%f", &rating);
    getchar();
    printf("Enter address              : ");
    scanf("%499[^\n]", address);
    getchar();
    printf("Enter description          : ");
    scanf("%999[^\n]", description);
    getchar();

    appendHotel(head, index, name, city, price_of_deluxe, price_of_single, price_of_villa, price_of_luxury, rating, address, description);
    writeHotelWithHeaders(*head);
}

void deleteHotel(Hotel** head, char* name, char* city) {
    Hotel* current = *head;
    Hotel* previous = NULL;
    int deleted = 0;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0 && strcmp(current->city, city) == 0) {
            if (previous == NULL) {
                *head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            deleted = 1;
            break;
        }
        previous = current;
        current = current->next;
    }

    if (deleted) {
        // Adjust the indices of the remaining hotels in the same city
        int index = 1;
        current = *head;
        while (current != NULL) {
            if (strcmp(current->city, city) == 0) {
                current->index = index++;
            }
            current = current->next;
        }
    }else{
        printf(red"\nHotel not found.\n"end);
        return;
    }

    writeHotelWithHeaders(*head);
    printf(green"\nHotel deleted successfully.\n"end);
}

void viewHotel(Hotel* head, char* name, char *city){
    Hotel* current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0 && strcmp(current->city, city) == 0) {
            printf("Name                 : %s\n", current->name);
            printf("City                 : %s\n", current->city);
            printf("Price of deluxe room : %d\n", current->price_of_deluxe);
            printf("Price of single room : %d\n", current->price_of_single);
            printf("Price of villa room  : %d\n", current->price_of_villa);
            printf("Price of luxury room : %d\n", current->price_of_luxury);
            printf("Rating               : %.2f\n", current->rating);
            printf("Address              : %s\n", current->address);
            printf("Description          : %s\n", current->description);
            return;
        }
        current = current->next;
    }
    printf(red"Hotel not found.\n"end);
}

void updateHotel(Hotel* head, char* name, char *city){
    Hotel* current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0 && strcmp(current->city, city) == 0) {
            printf("Enter new name                 : ");
            scanf("%99[^\n]", current->name);
            printf("Enter new price of deluxe room : ");
            scanf("%d", &current->price_of_deluxe);
            printf("Enter new price of single room : ");
            scanf("%d", &current->price_of_single);
            printf("Enter new price of villa room  : ");
            scanf("%d", &current->price_of_villa);
            printf("Enter new price of luxury room : ");
            scanf("%d", &current->price_of_luxury);
            printf("Enter new rating               : ");
            scanf("%f", &current->rating);
            getchar();
            printf("Enter new address              : ");
            scanf("%499[^\n]", current->address);
            getchar();
            printf("Enter new description          : ");
            scanf("%999[^\n]", current->description);
            getchar();
            writeHotelWithHeaders(head);
            printf(green"\nHotel updated successfully.\n"end);
            return;
        }
        current = current->next;
    }
    printf(red"\nHotel not found.\n"end);
}

int main(void){
    clear_console();
    print_UI();
    int flag = 1;
    char username[51], password[31];
    
    FILE* fp = fopen("hotelList.csv", "r");
    char buffer[1024];
    Hotel* hotelList = NULL;
    fgets(buffer, sizeof(buffer), fp);
    while(fgets(buffer, sizeof(buffer), fp)){
        int index = atoi(strtok(buffer, ","));
        char* name = strtok(NULL, ",");
        char *city = strtok(NULL, ",");
        int price_of_deluxe = atoi(strtok(NULL, ","));
        int price_of_single = atoi(strtok(NULL, ","));
        int price_of_villa = atoi(strtok(NULL, ","));
        int price_of_luxury = atoi(strtok(NULL, ","));
        float rating = atof(strtok(NULL, ","));
        char* address = strtok(NULL, ",");
        char* description = strtok(NULL, ",");
        description[strcspn(description, "\n")] = '\0'; // Remove trailing newline
        appendHotel(&hotelList, index, name, city, price_of_deluxe, price_of_single, price_of_villa, price_of_luxury, rating, address, description); // Add to the linked list
    }

    while (flag){
        printf("Enter username: ");
        scanf("%50[^\n]", username);
        getchar();
        printf("Enter password: ");
        scanf("%30[^\n]", password);
        getchar();
        if (strcmp(username,"admin")==0 && strcmp(password,"admin")==0){
            f_string_format(1,green"Welcome Admin!"end);
            flag = 0;
            SLEEP(3);
            clear_console();
        }
        else{
            f_string_format(1,red"Invalid credentials\n"end);
            SLEEP(3);
            clear_console();
            print_UI();
        }
    }

    char option;
    while (1) {
        print_UI();
        printf("\nAdd Hotel(A)/Delete Hotel(D)/Update Hotel(U)/View Hotel(V)/Exit(E): ");
        scanf(" %c", &option);
        getchar();
        printf("\n");
        if (option == 'A' || option == 'a') {
            addHotel(&hotelList);
            printf(green"\nHotel added successfully.\n"end);
        } else if (option == 'D' || option == 'd') {
            char name[100], city[100];
            printf("Enter hotel name: ");
            scanf("%99[^\n]", name);
            getchar();
            printf("Enter city: ");
            scanf("%99[^\n]", city);
            getchar();
            deleteHotel(&hotelList, name, city);
        } else if (option == 'U' || option == 'u') {
            char name[100], city[100];
            printf("Enter hotel name: ");
            scanf("%99[^\n]", name);
            getchar();
            printf("Enter city: ");
            scanf("%99[^\n]", city);
            getchar();
            printf("\n");
            updateHotel(hotelList, name, city);
        } else if (option == 'V' || option == 'v') {
            char name[100], city[100];
            printf("Enter hotel name: ");
            scanf("%99[^\n]", name);
            getchar();
            printf("Enter city: ");
            scanf("%99[^\n]", city);
            getchar();
            printf("\n");
            viewHotel(hotelList, name, city);
        }else if (option == 'E' || option == 'e') {
            freeMemory(hotelList);
            clear_console();
            return 0;
        }else{
            printf(red"Invalid option.\n"end);
        }
        printf("\nPress Enter to continue...");
        getchar();
        clear_console();
    }
}