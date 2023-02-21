#include <stdio.h>
/**
 * main _ entry point
 *
 * Return: 0
 */
int main(void)
{
	int i;
	for (i = 0 ; 1 < 10 ; i++)
	{
		putchar(i + '0');
		if (i != 9)
		{
			putchar(',');
			putchar(' ');
		}
	}
	putchar('\n');
	return (0);
}

