#include "image.h"
#include "img_proc_seq.h"

int flip_seq(const Image *input_img_ptr, Image *output_img_ptr)
{
	// flip sequentially
	int base_idx = 0;
	for (int i = 0; i < n_row; ++i)
	{
		int idx = 0;
		for (int j = 0; j < n_col; ++j)
		{
			(*output_img_ptr)->arr[base_idx + n_col - idx] = input_img_ptr->arr[base_idx + idx];
			++idx;
		}
		base_idx += n_col;
	}

	return 0;
}

int rgb2gray_seq(const Image *input_img_ptr, Image *output_img_ptr)
{
	// convert rgb to grayscale 
	int idx = 0;
	for (int i = 0; i < n_row; ++i)
	{
		for (int j = 0; j < n_col; ++j)
		{
			(*output_img_ptr)->arr[idx] = input_img_ptr->arr[idx];
			++idx;
		}
	}

	return 0;
}


int smoothing_seq(const Image *input_img_ptr, Image **output_img_ptr)
{

}
