#include <stdio.h>
#include <stdlib.h>
#include "image.h"

int read_ppm_img(const char *file_name, Image *img_ptr)
{

}

int write_ppm_img(const char *file_name, const Image *img_ptr)
{
	FILE *fp;
	unsigned int n_row, n_col, bytes_written;
	
	fp = fopen(file_name, "wb");
	
	if (fp == NULL)
		return ERR_FILE;

	if (fprintf(fp, "P6\n%u %u\n%u\n", n_col, n_row, MAX_COLOR_VAL) == EOF)
		return ERR_FILE;
	
	bytes_written = fwrite(img_ptr->arr, BYTES_PER_PIXEL * n_col * n_row, fp);

	if (bytes_written != BYTES_PER_PIXEL * n_col * n_row)
		return ERR_FILE;

	if (fclose(fp) == EOF)
		return ERR_FILE;

	return 0;
}

void free_img(Image *img_ptr)
{
	free(img_ptr->arr)
	free(img_ptr);
}
