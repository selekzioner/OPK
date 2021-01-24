#define _CRT_SECURE_NO_WARNINGS
#include "rational.h"

int compare_test(int a_num, int a_den, int b_num, int b_den) {
	Rational a, b;
	rat_create(&a, a_num, a_den);
	rat_create(&b, b_num, b_den);

	return rat_compare(&a, &b);
}

bool arithmetic_test (int a_num, int a_den, int b_num, int b_den, int true_res_num, int true_res_den,
	void operation (Rational*, Rational*, Rational*)) {
	Rational a, b, res, true_res;

	rat_create(&a, a_num, a_den);
	rat_create(&b, b_num, b_den);

	operation (&res, &a, &b);

	rat_create(&true_res, true_res_num, true_res_den);

	if (rat_compare(&res, &true_res) == 0)
		return true;
	else 
		return false;
}

bool power_test(int a_num, int a_den, int true_res_num, int true_res_den, int power) {
	Rational a, res, true_res;

	rat_create(&a, a_num, a_den);
	rat_power(&res, &a, power);

	rat_create(&true_res, true_res_num, true_res_den);

	if (rat_compare(&res, &true_res) == 0)
		return true;
	else 
		return false;
}

bool int_test(int a, int b, int true_res) {
	Rational r;
	rat_create(&r, a, b);
	if (rat_to_i(&r) == true_res)
		return true;
	else 
		return false;
}

bool double_test (int a, int b, double true_res) {
	Rational r;
	rat_create(&r, a, b);
	if (rat_to_d(&r) == true_res)
		return true;
	else 
		return false;
}

bool file_test(int a, int b) {
	Rational res;
	int a_tmp, b_tmp;
	FILE* fp = fopen("output.txt", "w+");
	if (fp == NULL) {
		printf("File doesn't open!\n");
		return 0;
	}
	rat_create(&res, a, b);
	rat_print(&res, fp);

	rewind(fp);
	if (getc(fp) == EOF) {
		printf("Error: Empty file\n");
		return false;
	}
	rewind(fp);

	if (res.numer == 0) {
		fscanf(fp, "%d", &a_tmp);
		b_tmp = 1;
	}
	else if (res.numer == res.denom){
		fscanf(fp, "%d", &a_tmp);
		b_tmp = 1;
    }
	else fscanf(fp, "%d/%d", &a_tmp, &b_tmp);
	fclose(fp);

	if (a_tmp == res.numer && (b_tmp == res.denom || res.numer == 0))
		return true;
	else 
		return false;
}

void tests() {
	assert(compare_test(3, 2, 2, 3) == 1);//compare
	assert(compare_test(4, 8, 2, 3) == -1);
	assert(compare_test(4, 8, 10001, 20002) == 0);
	assert(compare_test(5, -8, -5, 8) == 0);
	assert(compare_test(5, -8, 5, 8) == -1);

	assert(arithmetic_test(3, 2, 2, 3, 13, 6, rat_add)); //add
	assert(arithmetic_test(-3, 2, 2, 3, -5, 6, rat_add));
	assert(arithmetic_test(0, -2, 2, 3, 2, 3, rat_add));
	assert(arithmetic_test(-3, -2, -2, -3, 13, 6, rat_add));
	assert(arithmetic_test(0, -2, 0, -3, 0, 1, rat_add));
	
	assert(arithmetic_test(3, 2, 2, 3, 5, 6, rat_sub)); //sub
	assert(arithmetic_test(3, -2, 2, -3, -5, 6, rat_sub));
	assert(arithmetic_test(55, 999, -1, 2, 1109, 1998, rat_sub));
	assert(arithmetic_test(3, -2, -2, -3, -13, 6, rat_sub));
	assert(arithmetic_test(0, 2, 2, -3, 2, 3, rat_sub));

	assert(arithmetic_test(3, 2, 2, 3, 1, 1, rat_mul)); //mul
	assert(arithmetic_test(-3, 2, 2, 3, -1, 1, rat_mul));
	assert(arithmetic_test(3, 2, 2, -3, -1, 1, rat_mul));
	assert(arithmetic_test(-3, -2, -2, -3, 1, 1, rat_mul));
	assert(arithmetic_test(0, 2, 2, 3, 0, 1, rat_mul));

	assert(arithmetic_test(3, 2, 2, 3, 9, 4, rat_div)); //div
	assert(arithmetic_test(-3, 2, -2, 3, 9, 4, rat_div));
	assert(arithmetic_test(-3, 2, -2, -3, 9, -4, rat_div));
	assert(arithmetic_test(-3, -2, -2, -3, 9, 4, rat_div));
	assert(arithmetic_test(0, 2, 2, 3, 0, 1, rat_div));

	assert(power_test(3, 2, 27, 8, 3)); //pow
	assert(power_test(-3, 2, 4, 9, -2));
	assert(power_test(-3, 2, 9, 4, 2));
	assert(power_test(11, -5, 14641, 625, 4));
	assert(power_test(-3, 2, -2, 3, -1));

	assert(int_test(3, 2, 2)); //to int
	assert(int_test(-3, 2, -2));
	assert(int_test(11, 4, 3));
	assert(int_test(-123, 9, -14));
	assert(int_test(0, 11, 0));

	assert(double_test(3, 2, (double) 3 / 2)); //to double
	assert(double_test(-3, 2, (double) -3 / 2));
	assert(double_test(11, 4, (double)11 / 4));
	assert(double_test(-123, 9, (double)-123 / 9));
	assert(double_test(0, 11, 0));

	assert(file_test(3, 2)); //file
	assert(file_test(-3, 2));
	assert(file_test(11, 4));
	assert(file_test(-123, 9));
	assert(file_test(0, 2));
	assert(file_test(1234, 1234));

	Rational r1, r2;
	rat_create(&r1, 1, 7);
	rat_create(&r2, 1, 6);
	rat_add(&r1, &r1, &r2);
	rat_print(&r1, stdout);
}