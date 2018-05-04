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

t_room			*new_room(int id, char *name, int x, int y)
{
	t_room *room;

	if (!(room = (t_room*)malloc(sizeof(t_room))))
		return (NULL);
	room->id = id;
	room->name = name;
	room->x = x;
	room->y = y;
	room->is_ant = 0;
	room->ant_id = 0;
	room->next = NULL;
	return (room);
}

static void		parse_start_end(char *line, t_farm *farm, int id)
{
	if (is_command(line) == start)
		(farm->start_id == -1) ? farm->start_id = id : ft_error();
	else if (is_command(line) == end)
		(farm->end_id == -1) ? farm->end_id = id : ft_error();
}

static int		check_same_name_cr(t_farm *farm, t_room *room)
{
	t_room *tmp;

	tmp = farm->head_room;
	while (tmp)
	{
		if ((tmp->x == room->x) && (tmp->y == room->y))
			return (0);
		else if (!ft_strcmp(tmp->name, room->name))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

static t_room	*create_room(int id, char *line)
{
	char	**a;
	t_room	*room;

	a = ft_strsplit(line, ' ');
	room = new_room(id, ft_strdup(a[0]), ft_atoi(a[1]), ft_atoi(a[2]));
	ft_free_arr(a);
	return (room);
}

void			read_rooms(t_farm *farm, char **line)
{
	int		id;
	t_room	*room;
	t_room	*tmp;

	id = 0;
	while (get_next_line(farm->in, line))
	{
		if ((farm->start_id == id || farm->end_id == id) && !is_room(*line))
			(is_command(*line) != comment) ? ft_error() : 0;
		if (is_room(*line))
		{
			room = create_room(id, *line);
			if (id++ == 0)
				farm->head_room = room;
			else
				check_same_name_cr(farm, room) ? tmp->next = room : ft_error();
			tmp = room;
		}
		else if (is_command(*line))
			parse_start_end(*line, farm, id);
		else
			break ;
		map_join(farm, *line);
	}
}
