// C program to encrypt/decrypt specified files in a given directory by modifying the individual bytes of the file.

#include "parse_args.h"
#include "encrypt.h"
#include "decrypt.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char helptext[] = {
	"Usage: ./bytemod [file]/[wildcard] [-option]\n"
	"\n"
	"Wildcards: .exe, .txt, etc.\n A .exe wildcard automatically matches for executable files in given directory, regardless of Linux executables not possessing a .exe file extension.\n"
	"\n"
	"Arguments:\n"
	" [file]		File to encrypt/decrypt\n"
	"Options:\n"
	" -r, --recursive	Check given directory and sub-directories for files with specified wildcard\n"
	" -e, --encrypt		Encrypt files\n"
	" -d, --decrypt		Decrypt files\n"
};

int main(int argc, char** argv) {
	char command[1024];
	char* parent_dir = strstr(argv[1], "/");
	char* copy = malloc(sizeof(char)*strlen(argv[1]));
	strcpy(copy, argv[1]);
	copy[parent_dir - argv[1]] = '\0';	
	
	if (argc < 3) {
		fprintf(stderr, "%s\n", helptext);
		exit(1);
	}
	
	size_t dir_len = strlen(argv[1]);
	char* wildcard = strstr(argv[1], ".");
	if (wildcard == NULL) {
		fprintf(stderr, "Error: missing wildcard\n%s\n", helptext);
		exit(2);
	}
	
	if (find_arg("-r", "--recursive", argv, argc)) {
		if (strncmp(wildcard, ".exe ", 5) == 0) {
			sprintf(command, "find %s -type f -executable", copy);
		} else {
			sprintf(command, "%s -type f -name \"*%s\"", copy, wildcard);
		}
	} else {
		if (strncmp(wildcard, ".exe ", 5) == 0) {
			sprintf(command, "find %s -maxdepth 1 -type f -executable", copy);
		} else  {
			sprintf(command, "find %s -maxdepth 1 -name \"*%s\"", copy, wildcard);
		}
	}
	
	FILE* fp = popen(command, "r");
	
	if (fp == NULL) {
		printf("Failed to execute command\n");
		return 1;
	}
	
	char* line = NULL;
	size_t len = 0;
	
	bool is_encrypt = find_arg("-e", "--encrypt", argv, argc);
	bool is_decrypt = find_arg("-d", "--decrypt", argv, argc);
	
	while ((len = getline(&line, &len, fp)) != -1) {
		if (is_encrypt && !is_decrypt) {
			line[len-1] = '\0';
			encrypt(line);
		} else if (is_decrypt && !is_encrypt) {
			line[len-1] = '\0';
			decrypt(line);
		} else {
			fprintf(stderr, "Error: missing encrypt/decrypt option\n%s\n", helptext);
			exit(54);
		}
	}
	
	return 0;
}
