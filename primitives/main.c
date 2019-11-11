#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <time.h>

#include "gen_random.h"

const int LOWER = 0;
const int UPPER = 100;

int main(int argc, char *argv[])
{
	int *send_buf, *recv_buf;
	double start_t, finish_t;
	int rank, n_process, n_integers;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &n_process);
	
	if (argc != 2)
	{
		printf("Process %d > Usage: mpirun -np <num processes> "
			"-hostfile <hostfile> %s <num integers>\n", rank, argv[0]);	
		MPI_Finalize();	
		exit(EXIT_FAILURE);
	}
	
	int i;
	for (i = 0; argv[i]; ++i)
		if (!isdigit(argv[1][i]))
		{
			printf("Process %d > Usage: mpirun -np <num processes> "
				"-hostfile <hostfile> %s <num integers>\n", rank, argv[0]);	
			MPI_Finalize();	
			exit(EXIT_FAILURE);
		}
	
	n_integers = atoi(argv[1]);
	srand(time(NULL) + rank);
	
	recv_buf = malloc(n_integers * sizeof(int));

	if (recv_buf == NULL)
	{
		printf("Process %d > Memory allocation failed!\n", rank);
		MPI_Finalize();	
		exit(EXIT_FAILURE);
	}

	send_buf = gen_random_ints_arr(LOWER, UPPER, n_integers);
	
	if (send_buf == NULL)
	{
		printf("Process %d > Memory allocation failed!\n", rank);
		free(recv_buf);
		MPI_Finalize();	
		exit(EXIT_FAILURE);
	}

	start_t = MPI_Wtime();
	int d, j;
	int n_loop = log2(n_process);
	for (d = 0; d < n_loop; ++d)
	{
		int parent_rank = (rank + pow(2, d));

		if (parent_rank < n_process)
			MPI_Send(send_buf, n_integers, MPI_INT, parent_rank, 0, MPI_COMM_WORLD);

		if (rank >= pow(2, d))
		{
			MPI_Recv(recv_buf, n_integers, MPI_INT, 
					MPI_ANY_SOURCE, MPI_ANY_TAG, 
						MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			for (j = 0; j < n_integers; ++j)
				send_buf[j] += recv_buf[j];
		}
	}
	finish_t = MPI_Wtime();
	
	printf("Proc %d > Elapsed time = %e seconds\n", rank, finish_t - start_t);
	
	MPI_Finalize();	

	free(recv_buf);
	free(send_buf);

	return 0;
}

