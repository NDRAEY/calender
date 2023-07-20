#include <stdio.h>
#include <stdbool.h>
#include <time.h>

unsigned int days_in_months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

char* months[12] = {
		"January",
		"February",
		"March",
		"April",
		"May",
		"June",
		"July",
		"August",
		"September",
		"October",
		"November",
		"December"
};

int dayofweek(int d, int m, int y) {
    int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    
    y -= m < 3;
    
    return (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
}

bool is_leap(int year) {
	return (year & 3) == 0 && ((year % 25) != 0 || (year & 15) == 0);
}

unsigned int days_in_month(unsigned int month, unsigned int year) {
	if(month == 1) {
		return is_leap(year) ? 29 : 28;
	}

	return days_in_months[month];
}

int month_by_name(char* name, int fallback) {
	for(int i = 0; i < 12; i++) {
		if(strcmp(months[i], name) == 0) {
			return i;
		}
	}

	return fallback;
}

int main(int argc, char** argv) {
	time_t unix_time = time(NULL);
	struct tm *ptm = localtime(&unix_time);

	int month = ptm->tm_mon;

	if(argc == 2) {
		month = month_by_name(argv[argc - 1], month);
	}

	char* days_of_week[7] = {
		"Sunday",
		"Monday",
		"Tuesday",
		"Wednesday",
		"Thursday",
		"Friday",
		"Saturday"	
	};

	int year = 1900 + ptm->tm_year;

	printf("%10s %d\n", months[month], year);

	for(int i = 0; i < 7; i++) {
		printf("%.2s ", days_of_week[i]);
	}

	printf("\n");

	unsigned int first_day = dayofweek(1, month + 1, year);

	printf("%*s", 3 * (first_day), "");

	for(unsigned int i = 1; i <= days_in_month(month, year); i++) {
		unsigned int dow = dayofweek(i, month + 1, year);

		if(dow == 0 && i != 1) {
			printf("\n");
		}

		if((int)i == ptm->tm_mday && ptm->tm_mon == month) {
			printf("\033[7m%2d\033[0m ", i);
			continue;
		}

		printf("%2d ", i);
	}

	printf("\n\n");
}
