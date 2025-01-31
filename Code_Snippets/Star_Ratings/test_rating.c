#include <stdio.h>
#include "rating.h" // Include the rating header file

int main() {
    // Ensure UTF-8 encoding on Windows
    #ifdef _WIN32
    // Set code page to UTF-8 for Windows
    SetConsoleOutputCP(CP_UTF8);
    #endif

    // Example rating
    float rating = 3.5;
    rating_to_stars(rating);

    return 0;
}
