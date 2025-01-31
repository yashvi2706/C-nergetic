#include <stdio.h>
#include "f_string.h"
#include <stdlib.h>
 int main(){
    int choice;
     do {
        // Display menu
        f_string_format(1, "\033[1m==============\033[0m");
        f_string_format(1, "\033[38;5;208m          TRIVAGO   \033[0m");
        f_string_format(1, "\033[1m  ==============\033[0m\n");
        f_string_format(0, "\033[33m City List\033[0m");
        f_string_format(0, "\033[33m 1. Mumbai\033[0m");
        f_string_format(0, "\033[33m 2. Delhi\033[0m");
        f_string_format(0, "\033[33m 3. Bangalore\033[0m");
        f_string_format(0, "\033[33m 4. Kolkata\033[0m");
        f_string_format(0, "\033[33m 5. Chennai\033[0m");
        f_string_format(0, "\033[33m 6. Udaipur\033[0m");
        f_string_format(0, "\033[33m 7. Ahmedabad\033[0m");
        f_string_format(0, "\033[33m 8. Goa\033[0m");
        f_string_format(0, "\033[33m 9. Manali\033[0m");
        f_string_format(0, "\033[33m 10. Hydrabad\033[0m");
        f_string_format(0, "\033[33m 11. Exit\033[0m");
        f_string_format(1, "\033[1m ==============================\033[0m\n");
        printf("Enter your choice of city by selecting the index number: ");
   
        scanf("%d", &choice);
        getchar();
        printf("\n"); // Clear newline character from input buffer

        switch (choice) {
            case 1:
                //function for city1;
                break;
            case 2:
                //function for city2;
                break;
            case 3:
                //function for city3;
                break;
            case 4:
                //function for city4;
                break;
            case 5:
                //function for city5;
                break;
            case 6:
                //function for city6;
                break;
            case 7:
                //function for city7;
                break;
            case 8:
                //function for city8;
                break;
            case 9:
                //function for city9;
                break;
            case 10:
                //function for city10;
                break;
            
            case 11:
                printf("Exiting Hotel list page. Goodbye!\n");
                //SLEEP(4);
                //freeMemory(next_node);  // Free all allocated memory
                break;

            default:
                printf("Invalid input. Please try again.\n");
        }
    } while (choice != 11);return 0;
 }