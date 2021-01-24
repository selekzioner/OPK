#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>

typedef struct _Rational {
	int numer;
	int denom;
} Rational;

void rat_create(Rational *res, int a, int b);

void rat_add(Rational *result, Rational *a, Rational *b);

void rat_sub(Rational *result, Rational *a, Rational *b);

void rat_mul(Rational *result, Rational *a, Rational *b);

void rat_div(Rational *result, Rational *a, Rational *b);

void rat_power(Rational *result, Rational *r, int power);

int rat_compare(Rational *a, Rational *b);

int rat_to_i(Rational *a);

double rat_to_d(Rational *a);

void rat_print(Rational *a, FILE *fp);