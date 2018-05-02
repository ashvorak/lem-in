/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 14:17:05 by oshvorak          #+#    #+#             */
/*   Updated: 2018/05/01 14:17:25 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

static int	move(t_path *path, t_farm *farm)
{
	t_room	*tmp;

	tmp = path->head_room;
	if (path->ants != path->ants_finish)
	{
		while (tmp->next)
		{
			if (tmp->next->is_ant)
			{
				tmp->is_ant = 1;
				tmp->next->is_ant = 0;
				tmp->ant_id = tmp->next->ant_id;
				(tmp->id == farm->end_id) ? path->ants_finish++ : 0;
			}
			tmp = tmp->next;
		}
		if (path->ants_go != path->ants)
		{
			path->ants_go++;
			tmp->ant_id = farm->ant_id_go++;
			tmp->is_ant = 1;
			(path->length == 1) ? path->ants_finish++ : 0;
		}
	}
	return (path->ants_finish);
}

static void	print_room(t_path *tmp, int id, int end_id)
{
	t_room *room;

	while (tmp)
	{
		room = tmp->head_room;
		while (room)
		{
			if (room->is_ant && room->ant_id == id)
			{
				ft_printf("L%d-%s ", room->ant_id, room->name);
				if (room->id == end_id)
				{
					room->is_ant = 0;
					room->ant_id = 0;
				}
				return ;
			}
			room = room->next;
		}
		tmp = tmp->next;
	}
}

static void	print_move(t_farm *farm)
{
	int		i;
	t_path	*tmp;

	i = 1;
	while (i < farm->ant_id_go)
	{
		tmp = farm->head_path;
		print_room(tmp, i, farm->end_id);
		i++;
	}
}

void		print_paths(t_farm *farm)
{
	int		ants_finish;
	t_path	*tmp;

	ants_finish = 0;
	while (ants_finish != farm->ants)
	{
		ants_finish = 0;
		tmp = farm->head_path;
		while (tmp)
		{
			ants_finish += move(tmp, farm);
			tmp = tmp->next;
		}
		print_move(farm);
		ft_printf("\n");
	}
}
