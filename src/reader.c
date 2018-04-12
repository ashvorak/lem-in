/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 12:51:57 by oshvorak          #+#    #+#             */
/*   Updated: 2018/04/12 11:59:18 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

static t_room	*new_room(int id)
{
	t_room *room;

	if (!(room = (t_room*)malloc(sizeof(t_room))))
		return (NULL);
	room->id = id;
	room->name = NULL;
	room->x = 0;
	room->y = 0;
	room->next = NULL;
	return (room);
}

void	read_rooms(int fd, t_farm *farm, char **line)
{
	int		id;
	char	**arr;
	t_room	*room;
	t_room	*tmp;

	id = 0;
	while (get_next_line(fd, line))
	{
		if (is_room(*line))
		{
			arr = ft_strsplit(*line, ' ');
			room = new_room(id);
			room->name = ft_strdup(arr[0]);
			room->x = ft_atoi(arr[1]);
			room->y = ft_atoi(arr[2]);
			if (id == 0)
			{
				farm->head_room = room;
				tmp = room;
			}
			else
			{
				tmp->next = room;
				tmp = room;
			}
            id++;
			ft_free_arr(arr);
		}
		else if (is_command(*line))
		{
			if (is_command(*line) == start)
				farm->start_id = id;
			else if (is_command(*line) == end)
				farm->end_id = id;
		}
		else
			break;
	}
}

int	farm_size(t_farm *farm)
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

int	 is_farm_name(t_farm *farm, char *name)
{
	t_room	*tmp;

	tmp = farm->head_room;
	while (tmp)
	{
		if (tmp->name == name)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	 ret_id(t_farm *farm, char *name)
{
	int 	id;
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

void	read_connections(int fd, t_farm *farm, char **line)
{
	int		i;
	int 	j;
	int 	x;
	int 	y;
	int		size;
	int		**connects;
	char 	**arr;

	i = 0;
	size = farm_size(farm);
	if (!(connects = (int**)malloc(sizeof(int*) * size)))
		exit(1);
	while (i < size)
	{
		if (!(connects[i] = (int*)malloc(sizeof(int) * size)))
			exit(1);
		j = 0;
		while (j < size)
			connects[i][j++] = 0;
		i++;
	}
	do
	{
		if (is_connection(*line, farm) || is_command(*line))
		{
			if (is_connection(*line, farm))
			{
				arr = ft_strsplit(*line, '-');
				x = ret_id(farm, arr[0]);
				y = ret_id(farm, arr[1]);
				connects[x][y] = 1;
				connects[y][x] = 1;
			}
		}
		else
			ft_error();
	} while (get_next_line(fd, line));
	farm->connects = connects;
}
