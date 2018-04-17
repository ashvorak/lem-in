#include "../inc/lem_in.h"

void wave_tracing(t_farm *farm)
{
	int i;
	int size;

	i = 0;
	size = farm_size(farm);
	farm->paths = ret_matrix(farm);
	while (i < size)
	{
		if (farm->connects[farm->start_id][i] == 1)
			
		i++;
	}
}
