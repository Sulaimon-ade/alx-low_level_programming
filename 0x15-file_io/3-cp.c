#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>
#include "main.h"

#define BUFFER_SIZE 1024

/**
 * main - main function
 * @error_and_exit - Prints an error message and exits the program
 * @exit_code: The exit code to be returned
 * @message: The error message format string
 * @...: Additional arguments for the error message format
 */
	void error_and_exit(int exit_code, const char *message, ...)
{
	va_list args;

	va_start(args, message);
	vfprintf(stderr, message, args);
	va_end(args);
	exit(exit_code);
}
	/*Copy the content of the source file to the destination file*/
	void copy_file(const char *file_from, const char *file_to)
{
	int fd_from, fd_to;
	ssize_t bytes_read, bytes_written;
	char buffer[BUFFER_SIZE];

	/* Open the source file */
	fd_from = open(file_from, O_RDONLY);
	if (fd_from == -1)
		error_and_exit(98, "Error: Can't read from file %s\n", file_from);

	/* Open the destination file */
	fd_to = open(file_to, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_to == -1)
		error_and_exit(99, "Error: Can't write to %s\n", file_to);

	/* Copy the content of the source file to the destination file */
	while ((bytes_read = read(fd_from, buffer, BUFFER_SIZE)) > 0)
	{
	bytes_written = write(fd_to, buffer, bytes_read);
	if (bytes_written == -1)
		error_and_exit(99, "Error: Can't write to %s\n", file_to);
	}

	if (bytes_read == -1)
		error_and_exit(98, "Error: Can't read from file %s\n", file_from);

	/* Close the file descriptors */
	if (close(fd_from) == -1)
		error_and_exit(100, "Error: Can't close fd %d\n", fd_from);
	if (close(fd_to) == -1)
		error_and_exit(100, "Error: Can't close fd %d\n", fd_to);
}

int main(int argc, char *argv[])
{
	const char *file_from, *file_to;

	if (argc != 3)
	{
		error_and_exit(97, "Usage: %s file_from file_to\n", argv[0]);
	}

	file_from = argv[1];
	file_to = argv[2];
	copy_file(file_from, file_to);

	return (0);
}

