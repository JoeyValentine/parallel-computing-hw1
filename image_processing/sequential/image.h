#ifndef __IMAGE__
#define __IMAGE__

typedef struct _Pixel
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
} Pixel;

typedef struct _Image
{
	unsigned int n_row;
	unsigned int n_col;
	Pixel **arr;
} Image;

int read_ppm_img(const char *file_name, Image *img_ptr);
int write_ppm_img(const char *file_name, const Image *img_ptr);
void free_img(Image *img_ptr);

#endif
