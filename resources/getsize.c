#include <stdio.h>

struct test {
	int a;
	char b;
	double c;
};

int main(void) {
	// Built-in types
	printf("Size of char: %lu byte\n", sizeof(char));
	printf("Size of unsigned char: %lu bytes\n", sizeof(unsigned char));
	printf("Size of signed char: %lu bytes\n", sizeof(signed char));
	printf("Size of int: %lu bytes\n", sizeof(int));
	printf("Size of unsigned int: %lu bytes\n", sizeof(unsigned int));
	printf("Size of short: %lu bytes\n", sizeof(short));
	printf("Size of unsigned short: %lu bytes\n", sizeof(unsigned short));
	printf("Size of long: %lu bytes\n", sizeof(long));
	printf("Size of unsigned long: %lu bytes\n", sizeof(unsigned long));
	printf("Size of long long: %lu bytes\n", sizeof(long long));
	printf("Size of unsigned long long: %lu bytes\n", sizeof(unsigned long long));
	printf("Size of float: %lu bytes\n", sizeof(float));
	printf("Size of double: %lu bytes\n", sizeof(double));
	printf("Size of long double: %lu bytes\n", sizeof(long double));

	// Pointer types
	printf("Size of char*: %lu bytes\n", sizeof(char*));
	printf("Size of int*: %lu bytes\n", sizeof(int*));
	printf("Size of float*: %lu bytes\n", sizeof(float*));
	printf("Size of double*: %lu bytes\n", sizeof(double*));
	printf("Size of void*: %lu bytes\n", sizeof(void*));

	// array and struct types
	printf("Size of an array of 10 int: %lu bytes\n", sizeof(int[10]));
	printf("Size of struct test: %lu bytes\n", sizeof(struct test));

	return 0;
}

