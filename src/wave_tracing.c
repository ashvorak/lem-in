#include "../inc/lem_in.h"

static int	fill_wt(t_farm *farm, int wt, int size, int j)
{
	int p;
	int q;
	int bool;

	p = j;
	q = 0;
	bool = 0;
	while (q < size)
	{
		if (farm->connects[p][q] == 1)
			if (farm->paths[p][q] == 0)
			{
				farm->paths[p][q] = wt;
				farm->paths[q][p] = wt;
				bool = 1;
			}
		q++;
	}
	return (bool);
}

static int	fill_path(t_farm *farm, int wt, int size)
{
	int i;
	int j;
	int bool;

	i = 0;
	bool = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (farm->paths[i][j] == wt - 1)
				fill_wt(farm, wt, size, j) ? bool = 1 : 0;
			j++;
		}
		i++;
	}
	return (bool);
}

void		wave_tracing(t_farm *farm)
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
	wt = 2;
	bool = 1;
	while (bool)
	{
		bool = fill_path(farm, wt, size);
		wt++;
	}
}
