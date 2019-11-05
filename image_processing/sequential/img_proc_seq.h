#ifndef __IMG_PROC_SEQ__
#define __IMG_PROC_SEQ__

#include "image.h"

void flip_seq(const Image *input_img_ptr, Image *output_img_ptr);
void rgb2gray_seq(const Image *input_img_ptr, Image *output_img_ptr);
void smoothing_seq(const Image *input_img_ptr, Image *output_img_ptr);

#endif
