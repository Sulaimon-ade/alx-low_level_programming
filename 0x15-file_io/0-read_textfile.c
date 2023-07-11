#include "main.h"
#include <stdlib.h>
/**
	* read_textfile - Reads a text file and prints it to the POSIX standard output
	* @filename: The name of the file to read
	* @letters: The number of letters to read and print
	*
	* Return: The actual number of letters it could read and print
	*/
ssize_t read_textfile(const char *filename, size_t letters)
{
	int fd;
	ssize_t read_bytes, write_bytes;
	char *buffer;

	if (filename == NULL)
	return (0);

	buffer = malloc(sizeof(char) * (letters + 1));
	if (buffer == NULL)
	return (0);

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
	free(buffer);
	return (0);
	}

	read_bytes = read(fd, buffer, letters);
	if (read_bytes == -1)
	{
		free(buffer);
		close(fd);
	return (0);
	}

	buffer[read_bytes] = '\0';

	write_bytes = write(STDOUT_FILENO, buffer, read_bytes);
	if (write_bytes == -1 || write_bytes != read_bytes)
	{
		free(buffer);
		close(fd);
	return (0);
	}

	free(buffer);
	close(fd);

	return (read_bytes);
}
