#include <stdio.h>
#include "exception.h"
#include "image.h"
#include "img_proc_seq.h"

int main(int argc, char *argv[])
{
	int exit_status = 0;
	Image *input_img_ptr;

	if (argc != 5)
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

	// flip the image	
	Image *flipped_img_ptr;

	exit_status = flip_seq(input_img_ptr, flipped_img_ptr);

	if (!exit_status)
	{
		print_exception_type(exit_status, argv[1]);
		exit(EXIT_FAILURE);
	}

	// reduce the image to grayscale
	Image *gray_img_ptr;

	exit_status = rgb2gray_seq(input_img_ptr, gray_img_ptr);

	if (!exit_status)
	{
		print_exception_type(exit_status, argv[1]);
		exit(EXIT_FAILURE);
	}
		
	// smooth the image
	Image *smoothed_img_ptr;
	
	exit_status = smoothing_seq(input_img_ptr, gray_img_ptr);

	if (!exit_status)
	{
		print_exception_type(exit_status, argv[1]);
		exit(EXIT_FAILURE);
	}

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

	// create grayscale image
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

	return 0;
}
