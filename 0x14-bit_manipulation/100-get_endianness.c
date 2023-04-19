#include "main.h"
/**
 * get_endianness - checks the endianness
 *
 * Return: 0 if big endian, 1 if little endian
 */
int get_endianness(void)
{
	int E;
	char *c;

	E = 1;
	c = (char *)&E;

	return (*c);
}
