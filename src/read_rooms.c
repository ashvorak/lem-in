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

t_room	*new_room(int id, char *name, int x, int y)
{
	t_room *room;

	if (!(room = (t_room*)malloc(sizeof(t_room))))
		return (NULL);
	room->id = id;
	room->name = name;
	room->x = x;
	room->y = y;
	room->is_ant = 0;
	room->next = NULL;
	return (room);
}

static void		parse_start_end(char **line, t_farm *farm, int id)
{
	if (is_command(*line) == start && farm->start_id == -1)
		farm->start_id = id;
	else if (is_command(*line) == end && farm->end_id == -1)
		farm->end_id = id;
}

static int check_same_coor(t_farm *farm, t_room *room)
{
	t_room *tmp;

	tmp = farm->head_room;
	while (tmp)
	{
		if ((tmp->x == room->x) && (tmp->y == room->y))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void			read_rooms(int fd, t_farm *farm, char **line)
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
			room = new_room(id, ft_strdup(arr[0]), ft_atoi(arr[1]), ft_atoi(arr[2]));
			if (id++ == 0)
				farm->head_room = room;
			else
			{
				!check_same_coor(farm, room) ? ft_error() : 0;
				tmp->next = room;
			}
			tmp = room;
			ft_free_arr(arr);
		}
		else if (is_command(*line))
			parse_start_end(line, farm, id);
		else
			break;
		map_join(farm, *line);
	}
	(farm->start_id == -1 || farm->end_id == -1) ? ft_error() : 0;
}
