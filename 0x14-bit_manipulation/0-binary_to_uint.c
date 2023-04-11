#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include <string.h>
/**
 * binary_to_uint - converts binary into and unsigned int
 * Return: Aways retun number if condition is met
 * @b: is a pointer pointing to a string
 * if char in b is not 1 or 0 return NULL
 */
unsigned int binary_to_uint(const char *b)
{
	unsigned int num = 0;
	int a;
	int len;

	if (b == NULL)
	{
	return (0);

	}

	len = strlen(b);

	for (a = 0; a < len; a++)

	{
	if (b[a] != '0' && b[a] != '1')
		return (0);

	num <<= 1;
	if (b[a] == '1')
		num += 1;
	}

	return (num);
}
