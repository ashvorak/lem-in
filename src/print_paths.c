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

static void	print_ans(t_farm *farm, t_room *room)
{
	if (!farm->color || farm->out != 1)
		ft_printf("{fd}L%d-%s", farm->out, room->ant_id, room->name);
	else
	{
		if (room->id == farm->end_id)
			ft_printf("{fd}{green}L%d{eoc}-%s",\
			farm->out, room->ant_id, room->name);
		else
			ft_printf("{fd}{red}L%d{eoc}-%s",\
			farm->out, room->ant_id, room->name);
	}
}

static int	print_room(t_farm *farm, t_path *tmp, int id, int end_id)
{
	t_room	*room;

	while (tmp)
	{
		room = tmp->head_room;
		while (room)
		{
			if (room->is_ant && room->ant_id == id)
			{
				print_ans(farm, room);
				farm->iter_len++;
				if (room->id == end_id)
				{
					room->is_ant = 0;
					room->ant_id = 0;
				}
				return (1);
			}
			room = room->next;
		}
		tmp = tmp->next;
	}
	return (0);
}

static void	print_move(t_farm *farm)
{
	int		i;
	int		bool;
	t_path	*tmp;

	i = 1;
	bool = 1;
	while (i < farm->ant_id_go)
	{
		(i != 1 && bool) ? ft_printf("{fd} ", farm->out) : 0;
		tmp = farm->head_path;
		bool = print_room(farm, tmp, i, farm->end_id);
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
		farm->algo_len++;
		ft_printf("{fd}\n", farm->out);
	}
}
