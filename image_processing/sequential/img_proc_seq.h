#ifndef __IMG_PROC_SEQ__
#define __IMG_PROC_SEQ__

#include "image.h"

#define N_FUNC 3

extern const char* function_names[N_FUNC];

void flip_seq(const Image *input_img_ptr, Image *output_img_ptr);
void rgb2gray_seq(const Image *input_img_ptr, Image *output_img_ptr);
void smoothing_seq(const Image *input_img_ptr, Image *output_img_ptr);
int gen_processed_img(const Image *input_img_ptr, const char* func_name)

#endif
