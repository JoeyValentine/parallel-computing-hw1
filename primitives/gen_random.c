#include "gen_random.h"

int* gen_random_ints_arr(int lower, int upper, int count)
{
	int *arr;
	arr = malloc(count * sizeof(int));	

	int i;
	for (i = 0; i < count; ++i)
		arr[i] = (rand() % (upper - lower + 1)) + lower; 
	
	return arr;
}
