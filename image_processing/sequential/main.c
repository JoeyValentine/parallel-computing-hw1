#include <stdlib.h>
#include "image.h"
#include "img_proc_seq.h"

int main(int argc, char *argv[])
{
	int exit_status = 0;
	Image *input_img_ptr;

	if (argc != 2 + N_FUNC)
	{
		print_exception_type(ERR_USE, argv[0]);
		exit(EXIT_FAILURE);
	}
	
	exit_status = read_ppm_img(argv[1], &input_img_ptr);
	
	if (exit_status)
	{
		print_exception_type(exit_status, argv[1]);
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < N_FUNC; ++i)
	{
		int exit_status = 0;
		printf("%s\n", argv[2 +i]);
		exit_status = gen_processed_img(input_img_ptr, func_names[i], argv[2 + i], func_arr[i]);
	
		if (exit_status)
		{
			print_exception_type(exit_status, argv[1]);
			exit(EXIT_FAILURE);
		}
	}

	free_img(input_img_ptr);

	return 0;
}
