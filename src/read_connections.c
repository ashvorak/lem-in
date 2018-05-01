/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_connections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 14:17:08 by oshvorak          #+#    #+#             */
/*   Updated: 2018/05/01 14:17:26 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

static int		farm_size(t_farm *farm)
{
	int		size;
	t_room	*tmp;

	size = 0;
	tmp = farm->head_room;
	while (tmp)
	{
		tmp = tmp->next;
		size++;
	}
	return (size);
}

static int		ret_id(t_farm *farm, char *name)
{
	int		id;
	t_room	*tmp;

	id = -1;
	tmp = farm->head_room;
	while (tmp)
	{
		if (!ft_strcmp(name, tmp->name))
			return (tmp->id);
		tmp = tmp->next;
	}
	return (id);
}

int				**ret_matrix(t_farm *farm)
{
	int i;
	int j;
	int **connects;

	i = 0;
	if (!(connects = (int**)malloc(sizeof(int*) * farm->size)))
		exit(1);
	while (i < farm->size)
	{
		if (!(connects[i] = (int*)malloc(sizeof(int) * farm->size)))
			exit(1);
		j = 0;
		while (j < farm->size)
			connects[i][j++] = 0;
		i++;
	}
	return (connects);
}

static void		put_connect(t_farm *farm, char *line)
{
	int		x;
	int		y;
	char	**arr;

	if (is_connection(line, farm) || is_command(line))
	{
		if (is_connection(line, farm))
		{
			arr = ft_strsplit(line, '-');
			x = ret_id(farm, arr[0]);
			y = ret_id(farm, arr[1]);
			farm->connects[y][x] = 1;
			farm->connects[x][y] = 1;
			ft_free_arr(arr);
		}
	}
	else
		ft_error();
}

void			read_connections(int fd, t_farm *farm, char **line)
{
	farm->size = farm_size(farm);
	farm->connects = ret_matrix(farm);
	put_connect(farm, *line);
	while (get_next_line(fd, line))
	{
		put_connect(farm, *line);
		map_join(farm, *line);
	}
}
