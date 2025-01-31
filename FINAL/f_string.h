#ifndef F_STRING_H
#define F_STRING_H

#ifdef _WIN32
#include <windows.h>
#define SLEEP(seconds) Sleep((seconds) * 1000)
#else
#include <unistd.h>
#define SLEEP(seconds) sleep(seconds)
#endif

#define orange "\033[38;5;208m"
#define end "\033[0m"
#define red "\033[31m"
#define green "\033[32m"
#define yellow "\033[33m"
#define whitebold "\033[1;37m"
#define bold "\033[1m"

#include <stdlib.h>

// Function to format and print a string
// Parameters:
// - align: 0 for left-aligned, 1 for center-aligned, 2 for right-aligned
// - format: the format string (like printf)
// - ...: additional arguments for formatting
void f_string_format(int align, const char* format, ...);

// Function to clear the console
void clear_console();
void Company_name();
void header(char ar[100]);
void footer();
int confirm_payment_fun();
void rating_to_stars(float rating);

// Function to get the terminal width
void print_border(char *border);

void date_d(char* buffer, size_t buffer_size);

#endif // F_STRING_H
