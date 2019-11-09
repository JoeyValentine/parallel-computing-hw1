#include "img_proc_seq.h"

func_t func_arr[N_FUNC] = {flip_seq, rgb2gray_seq, smoothing_seq};

const char* func_names[N_FUNC] =
{
	"flip_seq",
	"rgb2gray_seq",
	"smoothing_seq"
};

void flip_seq(const Image *input_img_ptr, Image *output_img_ptr)
{
	// flip sequentially
	int base_idx = 0;
	unsigned int n_row = input_img_ptr->n_row;
	unsigned int n_col = input_img_ptr->n_col;

	for (int i = 0; i < n_row; ++i)
	{
		int idx = 0;
		for (int j = 0; j < n_col; ++j)
		{
			output_img_ptr->arr[base_idx + n_col - idx] = input_img_ptr->arr[base_idx + idx];
			++idx;
		}
		base_idx += n_col;
	}
}

void rgb2gray_seq(const Image *input_img_ptr, Image *output_img_ptr)
{
	// convert rgb to grayscale 
	int idx = 0;
	unsigned int n_row = input_img_ptr->n_row;
	unsigned int n_col = input_img_ptr->n_col;
	
	for (int i = 0; i < n_row; ++i)
	{
		for (int j = 0; j < n_col; ++j)
		{
			unsigned char avg_val = (input_img_ptr->arr[idx].r 
						+ input_img_ptr->arr[idx].g
						+ input_img_ptr->arr[idx].b) / 3;
			output_img_ptr->arr[idx].r = avg_val;
			output_img_ptr->arr[idx].g = avg_val;
			output_img_ptr->arr[idx].b = avg_val;
			++idx;
		}
	}
}

void smoothing_seq(const Image *input_img_ptr, Image *output_img_ptr)
{
	/*
	// convert rgb to grayscale 
	int idx = 0;
	for (int i = 0; i < n_row; ++i)
	{
		for (int j = 0; j < n_col; ++j)
		{
			(*output_img_ptr)->arr[idx] = (input_img_ptr->arr[idx].r 
							+ input_img_ptr->arr[idx].g
							 + input_img_ptr->arr[idx].b) / 3;
			++idx;
		}
	}
	*/
}

int gen_processed_img(const Image *input_img_ptr, const char *func_name,
			const char *file_name, func_t img_processing_func)
{
	int exit_status = 0;
	Image *output_img_ptr;
	double start_time, finish_time, elapsed_time;
	
	exit_status = gen_same_shape_img(input_img_ptr, &output_img_ptr);

	if (exit_status)
	{
		print_exception_type(exit_status, file_name);
		exit(EXIT_FAILURE);
	}

	start_time = get_cur_time();
	img_processing_func(input_img_ptr, output_img_ptr);
	finish_time = get_cur_time();
	elapsed_time = finish_time - start_time;
	printf("Execution time of %s() : %e\n", func_name, elapsed_time);
	
	exit_status = write_ppm_img(file_name, output_img_ptr);
	
	if (exit_status)
	{
		print_exception_type(exit_status, file_name);
		exit(EXIT_FAILURE);
	}
	
	free_img(output_img_ptr);
	
	return 0;
}
