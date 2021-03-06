/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wave_tracing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 14:17:13 by oshvorak          #+#    #+#             */
/*   Updated: 2018/05/01 14:17:26 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

static int	fill_wt(t_farm *farm, int wt, int j)
{
	int p;
	int q;
	int bool;

	p = j;
	q = 0;
	bool = 0;
	while (q < farm->size)
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

static int	fill_path(t_farm *farm, int wt)
{
	int i;
	int j;
	int bool;

	i = 0;
	bool = 0;
	while (i < farm->size)
	{
		j = 0;
		while (j < farm->size)
		{
			if (farm->paths[i][j] == wt - 1)
				fill_wt(farm, wt, j) ? bool = 1 : 0;
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

	i = 0;
	bool = 1;
	wt = 2;
	farm->paths = ret_matrix(farm);
	while (i < farm->size)
	{
		if (farm->connects[farm->start_id][i] == 1)
		{
			farm->paths[farm->start_id][i] = 1;
			farm->paths[i][farm->start_id] = 1;
		}
		i++;
	}
	while (bool)
	{
		bool = fill_path(farm, wt);
		wt++;
	}
}
