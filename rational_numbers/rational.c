#include "rational.h"

static int gcd(int a, int b) {
	while (a != 0 && b != 0)
		if (a >= b)
			a %= b;
		else
			b %= a;

	return a + b;
}

static int abs(int a) {
	if (a >= 0)
		return a;
	else
		return -a;
}

static void normalize(Rational* a) {
	int d = gcd(abs(a->numer), abs(a->denom));
	a->numer = a->numer / d;
	a->denom = a->denom / d;
}

static bool check_denom(Rational* a) {
	return (a->denom != 0);
}

static void pos_denom(Rational *a) {
	if (a->denom < 0) {
		assert(a->denom != INT_MIN);
		a->numer = -a->numer;
		a->denom = -a->denom;
	}
}

void rat_create(Rational *res, int n, int d) {
	assert(d != 0);

	res->numer = n;
	res->denom = d;
	pos_denom(res);

	assert(res->denom > 0);
	normalize(res);
}

void rat_add(Rational *result, Rational *a, Rational *b) {
	assert(check_denom(a) && check_denom(b));
	int d = gcd(a->denom, b->denom);
	int res_den = a->denom / d * b->denom;
	int res_num = b->denom / d * a->numer + a->denom / d * b->numer;
	
	result->denom = res_den;
	result->numer = res_num;
	normalize(result);
}

void rat_sub(Rational *result, Rational *a, Rational *b) {
	assert(check_denom(a) && check_denom(b));

		int d = gcd(a->denom, b->denom);
		result->denom = a->denom * b->denom / d;
		result->numer = a->numer * b->denom / d - b->numer * a->denom / d;

		normalize(result);
}

void rat_mul(Rational *result, Rational *a, Rational *b) {
	assert(check_denom(a) && check_denom(b));

		result->numer = a->numer * b->numer;
		result->denom = a->denom * b->denom;
		normalize(result);
}

void rat_div(Rational *result, Rational *a, Rational *b) {
	assert(check_denom(a) && check_denom(b));
	//b isn't broken now
	result->numer = a->numer * b->denom;
	result->denom = a->denom * b->numer;
	pos_denom(result);

	assert(check_denom(result));
	normalize(result);
}

void rat_power(Rational *result, Rational *r, int power) {
	assert(check_denom(r));
		if (power < 0) {
			power = -power;
			rat_create(r, r->denom, r->numer);
		}

		result->numer = 1;
		result->denom = 1;

		while (power != 0)
			if (power % 2 == 1) {
				result->numer *= r->numer;
				result->denom *= r->denom;
				power--;
			} else {
				r->numer *= r->numer;
				r->denom *= r->denom;
				power /= 2;
			}
		normalize(result);
}

int rat_compare(Rational *a, Rational *b) {
	assert(check_denom(a) && check_denom(b));

	int lcm = a->denom * b->denom / gcd(a->denom, b->denom);
	int a_cmp = a->numer * (lcm / a->denom);
	int b_cmp = b->numer * (lcm / b->denom);

	if (a_cmp < b_cmp)
		return -1;
	else if (a_cmp > b_cmp)
		return 1;
	else 
			return 0;
}

int rat_to_i(Rational *a) {
	assert(check_denom(a));

	double tmp = (double)a->numer / (double)a->denom;
	int i_tmp = (int)tmp;

	if (tmp - i_tmp <= -0.5)
		return i_tmp - 1;

	if (tmp - i_tmp >= 0.5 || tmp - i_tmp <= -0.5)
		return i_tmp + 1;

	else 
		return i_tmp;
}

double rat_to_d(Rational *a) {
	assert(check_denom(a));
	return (double)a->numer / (double)a->denom;
}

void rat_print(Rational *a, FILE *fp) {
	assert(check_denom(a));

	if (a->numer == 0)
		fprintf(fp, "0\n");
	else if (a->numer == a->denom)
		fprintf(fp, "1\n");
	else
		fprintf(fp, "%d/%d\n", a->numer, a->denom);
}