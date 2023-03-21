#ifndef parse_args_h
#define parse_args_h

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool find_arg(char* option1, char* option2, char** argv, size_t arg_count) {
	size_t index = 1;
	while (index < arg_count) {
		if ((strcmp(option1, argv[index]) * strcmp(option2, argv[index])) == 0) {
			return true;
		}
		
		index++;
	}
	
	return false;
}

#endif
