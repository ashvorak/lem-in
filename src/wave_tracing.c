#include "../inc/lem_in.h"

static int fill_path(t_farm *farm, int wt, int size)
{
	int i;
	int j;
	int tmp;
	int bool;

	i = 0;
	bool = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (farm->paths[i][j] == wt - 1)
			{
				tmp = j;
				j = 0;
				bool = 1;
				while (j < size)
				{
					if (farm->connects[tmp][j] == 1)
					{
						farm->paths[tmp][j] == 0 ? farm->paths[tmp][j] = wt : 0;//если вт меньше то ок
						farm->paths[j][tmp] == 0 ? farm->paths[j][tmp] = wt : 0;
					}
					j++;
				}
				break;
			}
			j++;
		}
		i++;
	}
	return (bool);
}

void wave_tracing(t_farm *farm)
{
	int i;
	int bool;
	int wt;
	int size;

	i = 0;
	size = farm_size(farm);
	farm->paths = ret_matrix(farm);
	while (i < size)
	{
		if (farm->connects[farm->start_id][i] == 1)
		{
			farm->paths[farm->start_id][i] = 1;
			farm->paths[i][farm->start_id] = 1;
		}
		i++;
	}
	ft_printf("\n");
	ft_printf("\n");
	wt = 2;
	bool = 1;
	while (bool && wt < 11)
	{
		bool = fill_path(farm, wt, size);
		wt++;
	}
}
