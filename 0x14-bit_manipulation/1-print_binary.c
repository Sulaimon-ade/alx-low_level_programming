#include <math.h>
#include "main.h"
/**
 * print_binary - prints the binary representation of a number
 * @n: num of printed
 * Return:binary
 */
void print_binary(unsigned long int n)
{
	unsigned long int dev, number;
	char flag;

	flag = 0;
	dev = pow(2, sizeof(unsigned long int) * 8 - 1);

	while (dev != 0)
	{
		number = n & dev;
		if (number == dev)
		{
			flag = 1;
			_putchar('1');

		}
		else if (flag == 1 || dev == 1)
		{
			_putchar('0');
		}
		dev >>= 1;
	}
}
