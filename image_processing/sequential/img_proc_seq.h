#ifndef __IMG_PROC_SEQ__
#define __IMG_PROC_SEQ__

#include "image.h"

int flip_seq(const Image *input_img_ptr, Image **output_img_ptr);
int rgb2gray_seq(const Image *input_img_ptr, Image **output_img_ptr);
int smoothing_seq(const Image *input_img_ptr, Image **output_img_ptr);

#endif
