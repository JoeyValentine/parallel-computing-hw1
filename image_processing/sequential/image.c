#include <stdio.h>
#include <stdlib.h>
#include "exception.h"
#include "image.h"

int read_ppm_img(const char *file_name, Image **img_ptr)
{
	FILE *fp;
	char buff[256] ={0,}, c;
	unsigned int n_row, n_col, max_color_val, bytes_read;
	
	fp = fopen(file_name, "rb");

	if (fp == NULL)
		return ERR_FILE;
	
	if (fgets(buff, sizeof(buff), fp) == EOF)
		return ERR_FORMAT;

	if (buff[0] != 'P' || buff[1] != '6')
		return ERR_FORMAT;

	*img_ptr = malloc(sizeof(Image));
	
	if (*img_ptr == NULL)
		return ERR_MEM;

	c = getc(fp);
    	while (c == '#') 
	{
		while (getc(fp) != '\n') ;
         	c = getc(fp);
    	}
    	ungetc(c, fp);

	if (fscanf(fp, "%u %u", &n_col, &n_row) != 2)
		return ERR_FORMAT;
	
	(*img_ptr)->n_col = n_col;
	(*img_ptr)->n_row = n_row;

    	if (fscanf(fp, "%d", &max_color_val) != 1)
		return ERR_FORMAT;

    	if (max_color_val!= MAX_COLOR_VAL)
		return ERR_FORMAT;

    	while (fgetc(fp) != '\n');

	(*img_ptr)->arr = malloc(n_row * n_col * sizeof(Pixel));
	
	if ((*img_ptr)->arr == NULL)
		return ERR_MEM;
	
    	bytes_read = fread((*img_ptr)->arr, sizeof(unsigned char), BYTES_PER_PIXEL * n_col * n_row, fp);
	
	if (bytes_read != BYTES_PER_PIXEL * n_col * n_row)
		return ERR_FILE;
	
	if (fclose(fp) == EOF)
		return ERR_FILE;

	return 0;
}

int write_ppm_img(const char *file_name, const Image *img_ptr)
{
	FILE *fp;
	unsigned int n_row, n_col, bytes_written;
	
	n_col = img_ptr->n_col;
	n_row = img_ptr->n_row;
	
	fp = fopen(file_name, "wb");
	
	if (fp == NULL)
		return ERR_FILE;

	if (fprintf(fp, "P6\n%u %u\n%u\n", n_col, n_row, MAX_COLOR_VAL) == EOF)
		return ERR_FILE;
	
	bytes_written = fwrite(img_ptr->arr, sizeof(unsigned char), BYTES_PER_PIXEL * n_col * n_row, fp);
	
	if (bytes_written != BYTES_PER_PIXEL * n_col * n_row)
		return ERR_FILE;

	if (fclose(fp) == EOF)
		return ERR_FILE;

	return 0;
}

int gen_same_shape_img(const Image *input_img_ptr, Image **output_img_ptr)
{
	unsigned int  n_row, n_col;
	
	n_row = input_img_ptr->n_row;
	n_col = input_img_ptr->n_col;
	
	*output_img_ptr = malloc(sizeof(Image));
	
	if (*output_img_ptr == NULL)
		return ERR_MEM;
	
	(*output_img_ptr)->n_col = n_col;
	(*output_img_ptr)->n_row = n_row;

	(*output_img_ptr)->arr = malloc(n_row * n_col * sizeof(Pixel));
	
	if ((*output_img_ptr)->arr == NULL)
		return ERR_MEM;
	
	return 0;
}

void free_img(Image *img_ptr)
{
	free(img_ptr->arr);
	free(img_ptr);
}
