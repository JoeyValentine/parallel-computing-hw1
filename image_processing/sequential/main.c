#include <stdio.h>
#include "exception.h"
#include "image.h"
#include "img_proc_seq.h"
#include "timer.h"

int main(int argc, char *argv[])
{
	int exit_status = 0;
	Image *input_img_ptr;

	if (argc != 2 + N_FUNC)
	{
		print_exception_type(ERR_USE, argv[0]);
		exit(EXIT_FAILURE);
	}
	
	// read an image
	exit_status = read_ppm_img(argv[1], input_img_ptr);
	
	if (!exit_status)
	{
		print_exception_type(exit_status, argv[1]);
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < N_FUNC; ++i)
		gen_processed_img(input_img_ptr, func_names[i], argv[2 + i], func_arr[i]);
	
	free_img(input_img_ptr);
/*
	// flip the image	
	Image *flipped_img_ptr;
	exit_status = gen_same_shape_img(input_img_ptr, &flipped_img_ptr);

	if (!exit_status)
	{
		print_exception_type(exit_status, argv[1]);
		exit(EXIT_FAILURE);
	}

	start_time = get_cur_time();
	flip_seq(input_img_ptr, flipped_img_ptr);
	finish_time = get_cur_time();
	elapsed_time = finish_time - start_time;
	printf("Execution time of flip_seq() : %e\n", elapsed_time);

	// reduce the image to grayscale
	Image *gray_img_ptr;
	exit_status = gen_same_shape_img(input_img_ptr, &gray_img_ptr);

	if (!exit_status)
	{
		print_exception_type(exit_status, argv[1]);
		exit(EXIT_FAILURE);
	}

	start_time = get_cur_time();
	rgb2gray_seq(input_img_ptr, gray_img_ptr);
	finish_time = get_cur_time();
	elapsed_time = finish_time - start_time;
	printf("Execution time of rgb2gray_seq() : %e\n", elapsed_time);
		
	// smooth the image
	Image *smoothed_img_ptr;
	exit_status = gen_same_shape_img(input_img_ptr, &smoothed_img_ptr);
	
	if (!exit_status)
	{
		print_exception_type(exit_status, argv[1]);
		exit(EXIT_FAILURE);
	}

	start_time = get_cur_time();
	smoothing_seq(input_img_ptr, smoothed_img_ptr);
	finish_time = get_cur_time();
	elapsed_time = finish_time - start_time;
	printf("Execution time of smoothing_seq() : %e\n", elapsed_time);

	// create flipped image
	exit_status = write_ppm_img(argv[2], flipped_img_ptr);
	
	if (!exit_status)
	{
		print_exception_type(exit_status, argv[2]);
		exit(EXIT_FAILURE);
	}

	// create grayscale image
	exit_status = write_ppm_img(argv[3], gray_img_ptr);
	
	if (!exit_status)
	{
		print_exception_type(exit_status, argv[3]);
		exit(EXIT_FAILURE);
	}

	// create smoothed image
	exit_status = write_ppm_img(argv[4], smoothed_img_ptr);
	
	if (!exit_status)
	{
		print_exception_type(exit_status, argv[4]);
		exit(EXIT_FAILURE);
	}
	
	// freeing the memory
	free_img(input_img_ptr);
	free_img(flipped_img_ptr);
	free_img(gray_img_ptr);
	free_img(smoothed_img_ptr);
*/
	return 0;
}
