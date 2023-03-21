#ifndef decrypt_h
#define decrypt_h
#include "debug.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void decrypt_buffer(uint8_t* buffer, size_t file_size) {
	size_t end_index = file_size;
	
	for (; end_index > 0;) {
		uint8_t temp = buffer[end_index - 1] - buffer[end_index];
		buffer[end_index - 1] = temp;
		end_index--;
	}
}

void decrypt(char* dir) {
#ifdef MIN_DEBUG_FLAG
	printf("decrypting %s\n", dir);
#endif

	FILE* file;
	file = fopen(dir, "rb");
	
	if (file == NULL) {
		fprintf(stderr, "Error: cannot open file '%s'.\n", dir);
	}
	
	fseek(file, 0L, SEEK_END);
	size_t file_size = ftell(file);
	rewind(file);
	
	uint8_t* decrypted_bytes = malloc(file_size * sizeof(uint8_t));
	
	if (decrypted_bytes == NULL) {
		fprintf(stderr, "Error: insufficient memory.\n");
		exit(32);
	}
	
	size_t bytes_read = fread(decrypted_bytes, sizeof(uint8_t), file_size, file);
	if (bytes_read < file_size) {
		fprintf(stderr, "Error: could not read file.\n");
		exit(33);
	}

#ifdef MAX_DEBUG_FLAG
	printf("-- bytes before decryption --\n    %ld bytes\n", file_size);
	print_buffer(decrypted_bytes, file_size);		
#endif	
	decrypt_buffer(decrypted_bytes, file_size);
	
	file = fopen(dir, "wb");
	
	if (file == NULL) {
		fprintf(stderr, "Error: cannot open file '%s'.\n", dir);
	}
	
	fwrite(decrypted_bytes, sizeof(uint8_t), file_size, file);

#ifdef MAX_DEBUG_FLAG
	printf("-- bytes after decryption --\n    %ld bytes\n", file_size);
	print_buffer(decrypted_bytes, file_size);	
#endif
	free(decrypted_bytes);
	
#ifdef MIN_DEBUG_FLAG
	printf("finished decrypting %s\n", dir);
#endif
}

#endif
