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
	// convert rgb to grayscale 
	int idx = 0;
	unsigned int n_row = input_img_ptr->n_row;
	unsigned int n_col = input_img_ptr->n_col;
	unsigned int x_pos[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
	unsigned int y_pos[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
	
	for (int i = 1; i < n_row - 1; ++i)
	{
		for (int j = 1; j < n_col - 1; ++j)
		{
			unsigned int avg_r_val = 0;
			unsigned int avg_g_val = 0;
			unsigned int avg_b_val = 0;
			
			for (int k = 0; k < 9; ++k)
			{
				unsigned int new_i = i + y_pos[k];
				unsigned int new_j = j + x_pos[k];

				avg_r_val += input_img_ptr->arr[n_col * new_i + new_j].r;
				avg_g_val += input_img_ptr->arr[n_col * new_i + new_j].g;
				avg_b_val += input_img_ptr->arr[n_col * new_i + new_j].b;
			}

			output_img_ptr->arr[idx].r = avg_r_val / 9;
			output_img_ptr->arr[idx].g = avg_g_val / 9;
			output_img_ptr->arr[idx].b = avg_b_val / 9;

			++idx;
		}
	}
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
