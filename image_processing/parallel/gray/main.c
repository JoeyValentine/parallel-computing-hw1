#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "exception.h"
#include "image.h"

int main(int argc, char *argv[])
{
	Image *input_img_ptr;
	int exit_status = 0, rank, n_process;

	if (argc != 3)
	{
		print_exception_type(ERR_USE, argv[0]);
		exit(EXIT_FAILURE);
	}
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &n_process);

	MPI_Datatype dt_pixel;
	MPI_Type_contiguous(3, MPI_UNSIGNED_CHAR, &dt_pixel);
	MPI_Type_commit(&dt_pixel);

	if (rank == 0)
	{	
		exit_status = read_ppm_img(argv[1], &input_img_ptr);
	
		if (exit_status)
		{
			print_exception_type(exit_status, argv[1]);
			MPI_Finalize();
			exit(EXIT_FAILURE);
		}

		unsigned int n_row = input_img_ptr->n_row;
		unsigned int n_col = input_img_ptr->n_col;
		
		Image *output_img_ptr;

		exit_status = gen_new_img(&output_img_ptr, n_row, n_col);
	
		if (exit_status)
		{
			print_exception_type(exit_status, argv[1]);
			free_img(input_img_ptr);
			MPI_Finalize();
			exit(EXIT_FAILURE);
		}

		double start_t, finish_t;
		start_t = MPI_Wtime();
		int i, receiver = 1;
		unsigned int params[2];
		unsigned int n_jobs = n_row / (n_process - 1);
		unsigned int more_jobs_idx = n_row % (n_process -1);

		params[0] = n_col;
		params[1] = n_jobs;

		for (i = 1; i < n_process; ++i)
		{
			if (i <= more_jobs_idx)
				params[1] = n_jobs + 1;
			else
				params[1] = n_jobs;
			MPI_Send(params, 2, MPI_UNSIGNED, i, 0, MPI_COMM_WORLD);
		}

		for (i = 0; i < n_row; ++i)
		{
			MPI_Send(&input_img_ptr->arr[n_col * i], n_col, dt_pixel, receiver, 0, MPI_COMM_WORLD);
			receiver = (receiver + 1) % n_process;
			if (receiver == 0)
				receiver += 1;
		}

		for (i = 0; i < n_row; ++i)
		{
			MPI_Recv(&output_img_ptr->arr[n_col * i], n_col, dt_pixel,
					MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
		
		finish_t = MPI_Wtime();
		printf("Elapsed time = %e seconds\n", finish_t - start_t);
		
		exit_status = write_ppm_img(argv[2], output_img_ptr);
	
		if (exit_status)
		{
			print_exception_type(exit_status, argv[2]);
			free_img(input_img_ptr);
			free_img(output_img_ptr);
			exit(EXIT_FAILURE);
		}
	
		free_img(input_img_ptr);
		free_img(output_img_ptr);
	}
	else
	{
		unsigned int n_col, n_jobs;
		unsigned int params[2]; //n_col, n_jobs

		MPI_Recv(params, 2, MPI_UNSIGNED,
				0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		
		n_col = params[0];
		n_jobs = params[1];		

		Pixel *recv_pixel_arr = malloc(params[0] * sizeof(Pixel));
		Pixel *send_pixel_arr = malloc(params[0] * sizeof(Pixel));
		
		int i;
		for (i = 0; i < n_jobs; ++i)
		{
			MPI_Recv(recv_pixel_arr, n_col, dt_pixel,
				0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		
			int j;
			for (j = 0; j < n_col; ++j)
			{	
				unsigned char avg_val = (recv_pixel_arr[j].r 
								+ recv_pixel_arr[j].g
								+ recv_pixel_arr[j].b) / 3;
				send_pixel_arr[j].r = avg_val;
				send_pixel_arr[j].g = avg_val;
				send_pixel_arr[j].b = avg_val;
			}
			
			MPI_Send(send_pixel_arr, n_col, dt_pixel, 0, 0, MPI_COMM_WORLD);
		}

		free(send_pixel_arr);
		free(recv_pixel_arr);
	}

	MPI_Finalize();

	return 0;
}

