#include <stdio.h>
#include "exception.h"

void print_exception_type(int exit_status, const char *file_name)
{
	switch (exit_status)
	{
		case ERR_MEM:
			printf("ERROR: Memory allocation failed!\n");
			break;
		case ERR_FORMAT:
			printf("ERROR: %s is not a valid ppm file!\n", file_name);
			break;
		case ERR_TRUNC:
			printf("ERROR: %s is truncated", file_name);
			break;
		case ERR_FILE:
			printf("ERROR: Error opening or closing %s", file_name);
			break;
		case ERR_USE:
			printf("Error: Usage %s <input-file> <flipped-file> "
				"<grayscale-file> <smoothed-file>\n", file_name);
			break;
	}
}
