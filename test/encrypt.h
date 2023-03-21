#ifndef encrypt_h
#define encrypt_h
#include "debug.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void encrypt_buffer(uint8_t* buffer, size_t file_size) {
	size_t start_index = 0;
	
	for (; start_index < (file_size - 1);) {
		uint8_t temp = buffer[start_index] + buffer[start_index + 1];
		buffer[start_index] = temp;
		start_index++;
	}
}

void encrypt(char* dir) {
#ifdef MIN_DEBUG_FLAG
	printf("encrypting %s\n", dir);
#endif
	FILE* file;
	file = fopen(dir, "rb");
	
	if (file == NULL) {
		fprintf(stderr, "Error: cannot open file '%s'.\n", dir);
	}
	
	fseek(file, 0L, SEEK_END);
	size_t file_size = ftell(file);
	rewind(file);
	
	uint8_t* encrypted_bytes = malloc(file_size * sizeof(uint8_t));
	
	if (encrypted_bytes == NULL) {
		fprintf(stderr, "Error: insufficient memory.\n");
		exit(32);
	}
	
	size_t bytes_read = fread(encrypted_bytes, sizeof(uint8_t), file_size, file);
	if (bytes_read < file_size) {
		fprintf(stderr, "Error: could not read file.\n");
		exit(33);
	}
	
#ifdef MAX_DEBUG_FLAG
	printf("-- bytes before encryption --\n    %ld bytes\n", file_size);
	print_buffer(encrypted_bytes, file_size);		
#endif
	encrypt_buffer(encrypted_bytes, file_size);
	file = fopen(dir, "wb");
	
	if (file == NULL) {
		fprintf(stderr, "Error: cannot open file '%s'.\n", dir);
	}
	
	fwrite(encrypted_bytes, sizeof(uint8_t), file_size, file);

#ifdef MAX_DEBUG_FLAG
	printf("-- bytes after encryption --\n    %ld bytes\n", file_size);
	print_buffer(encrypted_bytes, file_size);	
#endif
	free(encrypted_bytes);
#ifdef MIN_DEBUG_FLAG
	printf("finished encrypting %s\n", dir);
#endif
}

#endif
