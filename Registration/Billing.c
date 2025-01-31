#include "../Code_Snippets/String_Alignment/f_string.h"
#include <stdio.h>
#define cr_green "\033[1;38;2;0;100;0m"
#define cr_yellow "\t \033[1;38;2;255;255;0m"
#define cr_w "\t \033[1;38;255;255;255m"
#include <locale.h>

int main()
{  
    setlocale(LC_ALL, "");

    clear_console();
    print_border("*");
    
    
    f_string_format(0,"\033[1;38;2;255;165;0mTrivago\033[0m\n");
    char arr[100];
    date_d(arr,sizeof(arr));
    f_string_format(2,"%s",arr);
    print_border("*");
    
    printf("\n");
    f_string_format(1,"\t\033[1;38;2;0;100;0mBilling Information\033[0m\n");

    print_border("-");
    print_border("-");
    f_string_format(1,"Price for the Room : 560");
    f_string_format(1,"Price for the stay : 59696");
    f_string_format(1,"Price for ext commodities : xtra emcekc");
    f_string_format(1, "Discount for you : ckdmckdmc");
    int a=21;
    f_string_format(1,"Payment to be made : %d",a);
    

   

    print_border("-");
    
    f_string_format(1,"Check out : cedce");
    f_string_format(1,"Check In : cece");
    f_string_format(1,"Hotel Name : cece");
    f_string_format(1,"Location : cecec");
    int b=265651;
    f_string_format(1,"\t Booking Date : %d",b);
    f_string_format(1,"Commodities : ");
    print_border("-");

    printf("\n \n \n \n");
    f_string_format(1,"Customer Care :");
    f_string_format(1,"email id :");
    f_string_format(1,"CompanyName\u00A9\n");
    }