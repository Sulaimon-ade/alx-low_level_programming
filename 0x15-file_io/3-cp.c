#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#define BUFFER_SIZE 1024

/**
 * main - Copies the content of a file to another file.
 * @argc: The number of arguments.
 * @argv: An array of pointers to the arguments.
 *
 * Return: 0 on success.
 */
int main(int argc, char *argv[])
{
	int file_from, file_to, bytes_read, bytes_written;
	char buffer[BUFFER_SIZE];

	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: %s file_from file_to\n", argv[0]);
		exit(97);
	}

	file_from = open(argv[1], O_RDONLY);
	if (file_from == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", argv[1]);
		exit(98);
	}

	file_to = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (file_to == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", argv[2]);
		close(file_from);
		exit(99);
	}

	do {
		bytes_read = read(file_from, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", argv[1]);
			close(file_from);
			close(file_to);
			exit(98);
		}

		bytes_written = write(file_to, buffer, bytes_read);
		if (bytes_written == -1)
		{
			dprintf(STDERR_FILENO, "Error: Can't write to %s\n", argv[2]);
			close(file_from);
			close(file_to);
			exit(99);
		}
	} while (bytes_read == BUFFER_SIZE);

	if (close(file_from) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", file_from);
		exit(100);
	}

	if (close(file_to) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", file_to);
		exit(100);
	}

	return (0);
}
