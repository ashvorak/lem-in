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

	id = 1;
	while (get_next_line(fd, line))
	{
		if (is_room(*line))
		{
			arr = ft_strsplit(*line, ' ');
			room = new_room(id);
			room->name = ft_strdup(arr[0]);
			room->x = ft_atoi(arr[1]);
			room->y = ft_atoi(arr[2]);
			if (id == 1)
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

void	read_connections(int fd, t_farm *farm, char **line)
{
	int		i;
	int		size;
	char	**connects;

	i = 0;
	size = 7;
	if (!(connects = (char**)malloc(sizeof(char*) * size)))
		exit(1);
	while (i < size)
	{
		connects[i] = ft_strnew(size);
		ft_bzero(connects[i++], size);
	}
	while (get_next_line(fd, line))
	{
		if (is_connection(*line, farm) || is_command(*line))
		{
			if (is_connection(*line, farm))
			{
				ft_printf("LOOOOOL");
			}
		}
		else
			ft_error();
	}
}
