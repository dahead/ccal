#include <stdio.h>
#include <time.h>

void print_calendar(FILE *output, int days_in_month, int start_day, int current_day_of_month) {
    // Array for weekday headers
    const char *headers[] = {"Mo", "Tu", "We", "Th", "Fr", "Sa", "Su"};

    // Print headers
    for (int i = 0; i < 7; i++) {
        fprintf(output, "%5s", headers[i]);
    }
    fprintf(output, "\n");

    // Calculate the number of leading spaces for the first week
    int day_counter = 1;
    for (int i = 0; i < start_day; i++) {
        fprintf(output, "     "); // 5 spaces for each empty day
    }

    // Print days of the month
    for (int i = start_day; i < 7; i++) {
        if (day_counter == current_day_of_month) {
            fprintf(output, " [%2d]", day_counter++);
        } else {
            fprintf(output, "%5d", day_counter++);
        }
    }
    fprintf(output, "\n");

    while (day_counter <= days_in_month) {
        for (int i = 0; i < 7 && day_counter <= days_in_month; i++) {
            if (day_counter == current_day_of_month) {
                fprintf(output, " [%2d]", day_counter++);
            } else {
                fprintf(output, "%5d", day_counter++);
            }
        }
        fprintf(output, "\n");
    }
}

int main() {
    // Get current date and time
    time_t now = time(NULL);
    struct tm *local = localtime(&now);

    int current_day_of_month = local->tm_mday;                // Current day
    int current_month = local->tm_mon + 1;                   // Current month (0-11, so add 1)
    int current_year = local->tm_year + 1900;                // Current year

    // Calculate the number of days in the current month
    int days_in_month;
    if (current_month == 2) { // February
        days_in_month = (current_year % 4 == 0 && (current_year % 100 != 0 || current_year % 400 == 0)) ? 29 : 28;
    } else if (current_month == 4 || current_month == 6 || current_month == 9 || current_month == 11) {
        days_in_month = 30;
    } else {
        days_in_month = 31;
    }

    // Determine the start day of the month (0 = Monday, ..., 6 = Sunday)
    struct tm first_day = {0};
    first_day.tm_mday = 1;
    first_day.tm_mon = current_month - 1;
    first_day.tm_year = current_year - 1900;
    mktime(&first_day);
    int start_day = (first_day.tm_wday + 6) % 7; // Adjust to make Monday = 0

    // Print the current date
    char date_buffer[50];
    strftime(date_buffer, sizeof(date_buffer), "%A, %d %B %Y", local);
    fprintf(stdout, "Today: %s\n\n", date_buffer);

    // Write calendar to STDOUT
    print_calendar(stdout, days_in_month, start_day, current_day_of_month);

    return 0;
}

