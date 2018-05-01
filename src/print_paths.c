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
	int		ant;
	t_room	*tmp;

	ant = path->first_ant + path->ants_finish;
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
				ft_printf("L%d-%s ", tmp->ant_id, tmp->name);
				(tmp->id == farm->end_id) ? path->ants_finish++ : 0;
				ant++;
			}
			tmp = tmp->next;
		}
		if (path->ants_go != path->ants)
		{
			ft_printf("L%d-%s ", farm->ant_id_go, tmp->name);
			path->ants_go++;
			tmp->ant_id = farm->ant_id_go++;
			tmp->is_ant = 1;
			(path->length == 1) ? path->ants_finish++ : 0;
		}
	}
	return (path->ants_finish);
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
		ft_printf("\n");
	}
}
