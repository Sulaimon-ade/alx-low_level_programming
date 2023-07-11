#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>

/**
 * get_osabi_name - Get the name of the OS/ABI based on the identifier
 * @osabi: The OS/ABI identifier
 * Return: The name of the OS/ABI
 */
const char *get_osabi_name(unsigned char osabi) {
		switch (osabi) {
		case ELFOSABI_SYSV: return "UNIX - System V";
		case ELFOSABI_HPUX: return "HP-UX";
		case ELFOSABI_NETBSD: return "NetBSD";
		case ELFOSABI_LINUX: return "Linux";
 		case ELFOSABI_SOLARIS: return "Sun Solaris";
		case ELFOSABI_IRIX: return "SGI Irix";
		case ELFOSABI_FREEBSD: return "FreeBSD";
		case ELFOSABI_TRU64: return "Compaq TRU64 UNIX";
		case ELFOSABI_ARM: return "ARM architecture";
		case ELFOSABI_STANDALONE: return "Standalone (embedded) application";
		default: return "Unknown";
	}
}

/**
 * get_type_name - Get the name of the ELF file type based on the identifier
 * @type: The ELF file type identifier
 * Return: The name of the ELF file type
 */
const char *get_type_name(Elf64_Half type) {
		switch (type) {
		case ET_NONE: return "NONE (No file type)";
		case ET_REL: return "REL (Relocatable file)";
		case ET_EXEC: return "EXEC (Executable file)";
		case ET_DYN: return "DYN (Shared object file)";
		case ET_CORE: return "CORE (Core file)";
		default: return "Unknown";
	}
}
/**
 * display_elf_header - Display the information in the ELF header of a file
 * @filename: The name of the file to analyze
 */
void display_elf_header(const char *filename) {
	int fd;
	Elf64_Ehdr elf_header;
	ssize_t bytes_read;
	int i;

	fd = open(filename, O_RDONLY);
	if (fd == -1) {
 	dprintf(2, "Error: Cannot open file %s\n", filename);
	exit(98);
	}

	bytes_read = read(fd, &elf_header, sizeof(elf_header));
	if (bytes_read != sizeof(elf_header)) {
 	dprintf(2, "Error: Cannot read ELF header from file %s\n", filename);
	close(fd);
	exit(98);
	}

 	printf("ELF Header:\n");
	printf("  Magic:   ");

	for (i = 0; i < EI_NIDENT; i++) {
 	printf("%02x ", elf_header.e_ident[i]);
	}
	printf("\n");

	printf("  Class:                             %d-bit\n", elf_header.e_ident[EI_CLASS] == ELFCLASS64 ? 64 : 32);
	printf("  Data:                              %s\n", elf_header.e_ident[EI_DATA] == ELFDATA2LSB ? "2's complement, little endian" : "2's complement, big endian");
	printf("  Version:                           %d (current)\n", elf_header.e_ident[EI_VERSION]);
	printf("  OS/ABI:                            %s\n", get_osabi_name(elf_header.e_ident[EI_OSABI]));
	printf("  ABI Version:                       %d\n", elf_header.e_ident[EI_ABIVERSION]);
	printf("  Type:                              %s\n", get_type_name(elf_header.e_type));
	printf("  Entry point address:               0x%lx\n", (unsigned long)elf_header.e_entry);

	close(fd);
}

/**
 * main - Entry point of the program
 * @argc: The number of command-line arguments
 * @argv: An array containing the command-line arguments
 * Return: 0 on success, 98 on invalid number of arguments
 */
int main(int argc, char *argv[]) {
	const char *filename;

	if (argc != 2) {
	dprintf(2, "Usage: %s elf_filename\n", argv[0]);
	exit(98);
	}

	filename = argv[1];
	display_elf_header(filename);

	return 0;
}
