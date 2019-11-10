#ifndef __IMG_PROC_SEQ__
#define __IMG_PROC_SEQ__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "exception.h"
#include "image.h"
#include "timer.h"

#define N_FUNC 3

typedef void (*func_t)(const Image*, Image*);

extern func_t func_arr[N_FUNC];
extern const char* func_names[N_FUNC];

void flip_seq(const Image *input_img_ptr, Image *output_img_ptr);
void rgb2gray_seq(const Image *input_img_ptr, Image *output_img_ptr);
void smoothing_seq(const Image *input_img_ptr, Image *output_img_ptr);
int gen_processed_img(const Image *input_img_ptr, const char *func_name,
			const char *file_name, func_t img_processing_func);

#endif
