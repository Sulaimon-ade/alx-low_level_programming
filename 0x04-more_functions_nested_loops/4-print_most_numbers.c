#include "main.h"

/**
 * print_most_numbers - Print the numbers since 0 up to 9
 *@i: Prints the numbers excluding 2 and 4
 * Return: The numbers since 0 up to 9
 */

void print_most_numbers(void)

{
	char i;

	for (i = '0'; i <= '9'; i++)
	{
	if (!(i == '2' || i == '4'))

	_putchar(i);
	}
	_putchar('\n');
}
