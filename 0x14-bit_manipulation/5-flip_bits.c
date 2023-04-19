#include "main.h"
/**
 * flip_bits - flip from one number to another.
 * @n: the first number
 * @m: the second number
 * Return: the number of bits needed to flip
 */
unsigned int flip_bits(unsigned long int n, unsigned long int m)
{
	unsigned long int difference, result;
	unsigned int x, y;

	x = 0;
	result = 1;
	difference = n ^ m;
	for (y = 0; y < (sizeof(unsigned long int) * 8); y++)
	{
		if (result == (difference & result))
			x++;
		result <<= 1;
	}

	return (x);
}
