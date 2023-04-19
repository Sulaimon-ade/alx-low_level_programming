#include <stdio.h>
#include "main.h"

/**
 * set_bit - sets the value of a bit to 1 at a given index.
 * @index: starting from 0
 * @n: pointer number of i
 * Return: 1 if it worked, or -1 if any error occurred
 */
int set_bit(unsigned long int *n, unsigned int index)
{
	unsigned long int u;

	if (index > (sizeof(unsigned long int) * 8 - 1))
		return (-1);
	u = 1 << index;
	*n = *n | u;

	return (1);
}
