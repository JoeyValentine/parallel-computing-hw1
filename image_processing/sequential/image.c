#include <stdio.h>
#include <stdlib.h>
#include "image.h"

int read_ppm_img(const char *file_name, Image *img_ptr)
{

}

int write_ppm_img(const char *file_name, const Image *img_ptr)
{

}

void free_img(Image *img_ptr)
{
	free(img_ptr->arr)
	free(img_ptr);
}
