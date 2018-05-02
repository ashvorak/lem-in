/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 14:16:57 by oshvorak          #+#    #+#             */
/*   Updated: 2018/05/01 14:17:23 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

static void		show_paths(t_farm *farm)
{
	t_path *tmp;
	t_room *room;
	t_room *start;

	start = ret_room(farm, farm->start_id);
	tmp = farm->head_path;
	ft_printf("{red}{bolid}--->PATHS<---{eoc}\n");
	while (tmp)
	{
		room = tmp->head_room;
		while (room)
		{
			ft_printf("{red}%s{green}<-", room->name);
			room = room->next;
		}
		ft_printf("{red}%s", start->name);
		ft_printf(" {blue}length = %d, ants = %d", tmp->length, tmp->ants);
		ft_putchar('\n');
		tmp = tmp->next;
	}
	ft_printf("{eoc}\n");
}

void			handle_flags(t_farm *farm, char **av, t_flag flag)
{
	int i;

	i = 0;
	while (av[i])
	{
		if (!ft_strcmp(av[i], "-p") && flag == path)
			show_paths(farm);
		else if (!ft_strcmp(av[i], "-l") && flag == algo)
			ft_printf("{seawave}ALGORITHM LENGTH = %d{eoc}\n", farm->algo_len);
		i++;
	}
}
