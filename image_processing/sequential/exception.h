#ifndef __EXCEPTION__
#define __EXCEPTION__

typedef enum _Exception
{
	ERR_MEM = 1, 
	ERR_FORMAT, 
	ERR_TRUNC, 
	ERR_FILE, 
	ERR_USE
} Exception;

void print_exception_type(int exit_status, const char *file_name);

#endif
