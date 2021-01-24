#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

int months[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
int months_31[] = { 1, 3, 5, 7, 8, 10, 12 };

int month_sum(int last) {
	int sum = 0;
	for (int i = 0; i < last-1; i++) {
		sum += months[i];
	}
	return sum;
}

bool search(int number, int str[]) {
	int i = 0;
	while (str[i]) {
		if (number == str[i]) {
			return true;
		}
		i++;
	}
	return false;
}

bool bissextile(int year) {
	return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

bool correct_date(int d, int m, int y) {
	if (d > 0 && m > 0 && m <= 12 && y <= 2019 && y >= 0) {
		if (m != 2) {
			if (search(m, months_31) && d < 32) {
				return true;
			}
			if (d < 31) {
				return true;
			}
		}
		else {
			if (!bissextile(y) && d < 29) {
				return true;
			}
			if (bissextile(y) && d < 30) {
				return true;
			}
		}
	} 
	return false;
}

int day_number(int d, int m, int y){
	if (correct_date(d, m, y)) {
		int n = d + month_sum(m);
		if (bissextile(y) && m>2) {
			return n+1;
		}else {
			return n;
		}
	}else{
		return -1;
	}
}

int main ()
{
	assert(day_number(-1, 2, 2000) == -1);
	assert(day_number(3, -45, 2000) == -1);
	assert(day_number(4, 14, 2000) == -1);
	assert(day_number(4, 10, 2300) == -1);
	assert(day_number(13, 9, 2019) == 256);
	assert(day_number(1, 3, 1304) == 61);
	assert(day_number(1, 3, 2000) == 61);
	assert(day_number(1, 3, 1300) == 60);
	assert(day_number(31, 12, 1300) == 365);
	assert(day_number(31, 12, 1304) == 366);
	assert(day_number(29, 2, 1300) == -1);
	assert(day_number(29, 2, 1304) == 60);
	assert(day_number(29, 2, 2001) == -1);
	return 0;
}