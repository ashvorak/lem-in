#include "libft.h"

void ft_free_arr_int(int **arr, int size)
{
	int i;

	i = 0;
	if (arr)
	{
		while (i < size)
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}

