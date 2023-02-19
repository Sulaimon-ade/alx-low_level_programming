#include <stdio.h>
/**
 * main - Prints the alphabet
 * Return: Always 0
 */
int main(void)
{
	char alp[26] = "abcdefghijklmnopqrstuvwxyz";
	int i;
	
	for (i = 0; i < 26; 1++)
	{
		putcher(alp[i]);
	}
	putchar('\n');
	return (0);
}
