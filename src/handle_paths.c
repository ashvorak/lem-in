/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 14:16:57 by oshvorak          #+#    #+#             */
/*   Updated: 2018/05/01 14:17:23 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

static t_path	*new_path(t_room *room)
{
	t_path *path;

	if (!room)
		return (NULL);
	if (!(path = (t_path*)malloc(sizeof(t_path))))
		return (NULL);
	path->ants = 0;
	path->ants_go = 0;
	path->ants_finish = 0;
	path->head_room = room;
	path->next = NULL;
	return (path);
}

t_room			*ret_room(t_farm *farm, int id)
{
	t_room *tmp;

	tmp = farm->head_room;
	while (id != tmp->id)
		tmp = tmp->next;
	return (tmp);
}

static int		cleaning(t_farm *farm, int id_way, int id_min)
{
	if (id_way != farm->end_id)
		clean_connect(farm, id_way);
	else if (id_way == farm->end_id && id_min == farm->start_id)
	{
		farm->connects[farm->start_id][farm->end_id] = 0;
		farm->connects[farm->end_id][farm->start_id] = 0;
	}
	return (id_min);
}

static t_room	*make_path(t_farm *farm)
{
	int		id_min;
	int		id_way;
	t_room	*room;
	t_room	*tmp;
	t_room	*head_room;

	id_way = farm->end_id;
	head_room = copy_room(ret_room(farm, farm->end_id));
	tmp = head_room;
	while (id_way != farm->start_id)
	{
		if ((id_min = find_min(farm, id_way)) == -1)
		{
			free_rooms(head_room);
			return (NULL);
		}
		if (id_min != farm->start_id)
		{
			room = copy_room(ret_room(farm, id_min));
			tmp->next = room;
			tmp = room;
		}
		id_way = cleaning(farm, id_way, id_min);
	}
	return (head_room);
}

void			handle_path(t_farm *farm)
{
	t_path	*buf;
	t_path	*path;
	t_room	*head_room;

	head_room = make_path(farm);
	path = new_path(head_room);
	while (path)
	{
		if (!farm->head_path)
			farm->head_path = path;
		else
			buf->next = path;
		buf = path;
		path->length = path_length(path);
		ft_free_arr_int(farm->paths, farm->size);
		wave_tracing(farm);
		head_room = make_path(farm);
		path = new_path(head_room);
	}
	(farm->head_path) ? allocation_ants(farm) : ft_error();
}
