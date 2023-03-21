#ifndef debug_h
#define debug_h

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_DEBUG_FLAG
#define MIN_DEBUG_FLAG

void print_chars(uint8_t* buffer, size_t l) {
	for (int i = l - 16; i < l; i++) {
		if (buffer[i] > 31 && buffer[i] < 127) {
			printf("%c", buffer[i]);
		} else {
			printf(".");
		}
	}
}

void print_buffer(uint8_t* buffer, int file_size) {
	printf("%08x  ", 0);
	for (size_t i = 0; i < file_size; i++) {
		if (i > 0 && i % 8 == 0) {
			printf("  ");
		}
		
		if (i > 0 && (i % 16 == 0)) {
			printf("|");
			print_chars(buffer, i);
			printf("|");
			printf("\n");
			printf("%08lx  ", i);
		}
		
		if (i < file_size) {
			printf("%02x ", buffer[i]);
		}
	}
	
	printf("\n");
}

#endif
