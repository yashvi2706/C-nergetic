#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "f_string.h"
#ifdef _WIN32
#include <windows.h>
#define SLEEP(seconds) Sleep((seconds) * 1000)
#else
#include <unistd.h>
#define SLEEP(seconds) sleep(seconds)
#endif
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
int main(){
    clear_console();
    FILE *f1=fopen("details.csv","w");
    FILE *f2=fopen("customer_choice.csv","r");
    int index;
    if(!f1)
        printf("File does not exist.\n");
    if(!f2)
        printf("File deos not exist.\n");
    else{
        char first_char=fgetc(f2);
        index=atoi(&first_char);}
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
        
        f_string_format(1, "\033[1m==============\033[0m");
        f_string_format(1, "\033[38;5;208m          TRIVAGO   \033[0m");
        f_string_format(1, "\033[1m  ==============\033[0m\n");
        printf("How many nights? ");
        int nights;
        scanf("%i",&nights);
        getchar();
        char date[10];
        printf("From which date? (Please enter in dd/mm/yyyy format) ");
        scanf("%s",date);
        getchar();
        printf("Select the room type:\n1 : Single Room\n2 : Deluxe Room\n3 : Villa\n4 : Luxury\n");
        int type_num;
        char type[15];
        int price;
        int i=0;
        while(!i){
            printf("Type number: ");
            scanf("%i",&type_num);
            getchar();
            if(type_num==1){strncpy(type,"Single",sizeof(type));price=hotels[i].price_of_single;i=1;}
            else if(type_num==2){strncpy(type,"Deluxe",sizeof(type));price=hotels[i].price_of_deluxe;i=1;}
            else if(type_num==3){strncpy(type,"Villa",sizeof(type));price=hotels[i].price_of_villa;i=1;}
            else if(type_num==4){strncpy(type,"Luxury",sizeof(type));price=hotels[i].price_of_luxury;i=1;}
            else{printf("Type correct number.\n");}}

        int adults,kids,rooms;
        int a=0;
        while(!a){
            printf("Enter the number of adults: ");
            scanf("%d",&adults);
            getchar();
            printf("Enter the number of kids: ");
            scanf("%d",&kids);
            getchar();
            printf("Enter the number of rooms needed: ");
            scanf("%d",&rooms);
            getchar();
            int r1 =0;
            if(adults%2==0){
                r1+=adults/2;
                if(kids>r1){
                    if((kids-r1)%3==0) r1+=(kids-r1)/3;
                    else r1+=(kids-r1)/3 + 1;
                }
            }
            else{
                r1+=adults/2 + 1;
                if(kids>r1){
                    if((kids-r1-1)%3==0){
                        r1+=(kids-r1-1)/3;}
                    else r1+=(kids-r1-1)/3 + 1;
                }
            }
            
            if(rooms<r1){
                printf("Minimum number of rooms needed are %d\n",r1);
                printf("Sorry you need to book %d more rooms to accomodate everyone.\n",r1-rooms);
            }
            else {printf("Congratulations, your rooms have been booked successfully!\n");a=1;}
        }
        SLEEP(4);
        clear_console();
        
        f_string_format(1, "\033[1m==============\033[0m");
        f_string_format(1, "\033[38;5;208m          TRIVAGO   \033[0m");
        f_string_format(1, "\033[1m  ==============\033[0m\n");
        char commodities[7];
        printf("Select extra commodities:(type 0 if you don't want or 1 if you want)\n");
        printf("Breakfast: ");
        scanf("%c",&commodities[0]);
        getchar();
        printf("Lunch: ");
        scanf("%c",&commodities[1]);
        getchar();
        printf("Dinner: ");
        scanf("%c",&commodities[2]);
        getchar();
        printf("Extra Bed: ");
        scanf("%c",&commodities[3]);
        getchar();
        printf("Spa: ");
        scanf("%c",&commodities[4]);
        getchar();
        printf("Pick-up Service: ");
        scanf("%c",&commodities[5]);
        getchar();
        printf("Pet-rooms: ");
        scanf("%c",&commodities[6]);
        getchar();
        fprintf(f1,"%i,%i,%s,%i,%s,%i,%i,%s\n",nights,rooms,type,price,date,adults,kids,commodities);
        fflush(f1);
        fclose(f1);
        SLEEP(2);
        //Idhar tumhara function daal dena jo bhi billing wala ho
        return 0;
        
    }}
   // FILE 1(for hotel):
   // name,city,price_of_single,price_of_deluxe,price_of_villa,price_of_luxury,address.

   // FILE 2(for price):
   // nights(int),no_of_rooms,room_type(string),date(string),no_of_adults,no_of_kids,extra(string: 01010101)
