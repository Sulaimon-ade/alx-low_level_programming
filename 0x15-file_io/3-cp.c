#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

#define BUFFER_SIZE 1024

/**
 * error_and_exit - Prints an error message and exits with a specified code
 * @exit_code: The exit code to exit with
 * @message: The error message to print
 * @filename: The name of the file
 */
void error_and_exit(int exit_code, const char *message, const char *filename)
{
    dprintf(2, message, filename);
    exit(exit_code);
}

/**
 * cp - Copies the content of a file to another file
 * @file_from: The name of the source file
 * @file_to: The name of the destination file
 *
 * Return: 0 on success, -1 on failure
 */
int cp(const char *file_from, const char *file_to)
{
    int fd_from, fd_to, bytes_read, bytes_written;
    char buffer[BUFFER_SIZE];

    if (file_from == NULL || file_to == NULL)
        error_and_exit(97, "Usage: cp file_from file_to\n", "");

    fd_from = open(file_from, O_RDONLY);
    if (fd_from == -1)
        error_and_exit(98, "Error: Can't read from file %s\n", file_from);

    fd_to = open(file_to, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_to == -1)
        error_and_exit(99, "Error: Can't write to %s\n", file_to);

    while ((bytes_read = read(fd_from, buffer, BUFFER_SIZE)) > 0)
    {
        bytes_written = write(fd_to, buffer, bytes_read);
        if (bytes_written == -1 || bytes_written != bytes_read)
            error_and_exit(99, "Error: Can't write to %s\n", file_to);
    }

    if (bytes_read == -1)
        error_and_exit(98, "Error: Can't read from file %s\n", file_from);

    if (close(fd_from) == -1)
        error_and_exit(100, "Error: Can't close fd", fd_from);

    if (close(fd_to) == -1)
       error_and_exit(100, "Error: Can't close fd", fd_to);

    return (0);
}

/**
 * main - Entry point of the program
 * @argc: The number of command-line arguments
 * @argv: An array of command-line argument strings
 *
 * Return: 0 on success, 1 on failure
 */
int main(int argc, char *argv[])
{
    if (argc != 3)
        error_and_exit(97, "Usage: cp file_from file_to\n", "");

    return (cp(argv[1], argv[2]));
}
