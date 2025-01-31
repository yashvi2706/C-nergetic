all: main registration admin login viewpage userpage selection billing
main: Main.c f_string.c
	gcc Main.c f_string.c -o main
registration: Registration.c f_string.c
	gcc Registration.c f_string.c -o registration
admin: Admin.c f_string.c
	gcc Admin.c f_string.c -o admin
login: Login.c f_string.c
	gcc Login.c f_string.c -o login
viewpage: ViewPage.c f_string.c
	gcc ViewPage.c f_string.c -o viewpage
userpage: user_page.c f_string.c
	gcc user_page.c f_string.c -o userpage
selection: selection.c f_string.c
	gcc selection.c f_string.c -o selection
billing: Billing.c f_string.c
	gcc Billing.c f_string.c -o billing
clean:
	rm -f main registration admin login viewpage userpage selection billing

