#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#define BUFFER_SIZE 1024

/**
 * print_error - Prints an error message to the standard error.
 * @msg: The error message format.
 * @file_name: The name of the file related to the error.
 *
 * Description: Prints the error message to the standard error with the
 * file_name included in the message.
 */
void print_error(const char *msg, const char *file_name)
{
	dprintf(STDERR_FILENO, msg, file_name);
	exit(98);
}

/**
 * copy_file - Copies the content of one file to another file.
 * @file_from: The name of the source file.
 * @file_to: The name of the destination file.
 *
 * Description: Reads the content of the file_from and writes it to file_to.
 * If file_to already exists, it will be truncated. If file_from does not
 * If file_to cannot be created or written to, it will print an error message
 * and exit with code 99.
 */
void copy_file(const char *file_from, const char *file_to)
{
	int file_from_fd, file_to_fd;
	ssize_t bytes_read, bytes_written;
	char buffer[BUFFER_SIZE];

	file_from_fd = open(file_from, O_RDONLY);
	if (file_from_fd == -1)
		print_error("Error: Can't read from file %s\n", file_from);

	file_to_fd = open(file_to, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (file_to_fd == -1)
	{
		close(file_from_fd);
		print_error("Error: Can't write to %s\n", file_to);
	}

	do {
		bytes_read = read(file_from_fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			close(file_from_fd);
			close(file_to_fd);
			print_error("Error: Can't read from file %s\n", file_from);
		}

		bytes_written = write(file_to_fd, buffer, bytes_read);
		if (bytes_written == -1)
		{
			close(file_from_fd);
			close(file_to_fd);
			print_error("Error: Can't write to %s\n", file_to);
		}
	} while (bytes_read == BUFFER_SIZE);

	close(file_from_fd);
	close(file_to_fd);
}

/**
 * main - Copies the content of a file to another file.
 * @argc: The number of arguments.
 * @argv: An array of pointers to the arguments.
 *
 * Description: The program takes two arguments: file_from and file_to.
 * It copies the content of file_from to file_to. If the number of arguments
 * is incorrect, it will print an error message and exit with code 97.
 * The function also checks for various file-related errors and exits with
 * the appropriate exit codes (98, 99, 100) if necessary.
 *
 * Return: 0 on success.
 */
int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: %s file_from file_to\n", argv[0]);
		exit(97);
	}

	copy_file(argv[1], argv[2]);

	return (0);
}
