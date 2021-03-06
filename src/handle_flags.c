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
	ft_printf("{fd}PATHS:\n", farm->out);
	while (tmp)
	{
		room = tmp->head_room;
		while (room)
		{
			ft_printf("{fd}%s<-", farm->out, room->name);
			room = room->next;
		}
		ft_printf("{fd}%s", farm->out, start->name);
		ft_printf("{fd} [length: %d, ants: %d]", \
		farm->out, tmp->length, tmp->ants);
		ft_printf("{fd}\n", farm->out);
		tmp = tmp->next;
	}
	ft_printf("{fd}\n", farm->out);
}

int				handle_flags_before(t_farm *farm, int ac, char **av)
{
	int i;

	i = 1;
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "-p"))
			show_paths(farm);
		else if (!ft_strcmp(av[i], "-c"))
			farm->color = 1;
		i++;
	}
	return (0);
}

int				valid_flags(int ac, char **av)
{
	int i;

	i = 1;
	while (i < ac)
	{
		if (ft_strcmp(av[i], "-i") && \
		ft_strcmp(av[i], "-l") && ft_strcmp(av[i], "-p") && ft_strcmp(av[i], \
		"-f") && ft_strcmp(av[i], "-c") && ft_strcmp(av[i], "-o"))
			ft_usage();
		if (!ft_strcmp(av[i], "-f") || !ft_strcmp(av[i], "-o"))
			i++;
		i++;
	}
	return (0);
}

int				handle_flags_after(t_farm *farm, int ac, char **av)
{
	int i;

	i = 1;
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "-i"))
			ft_printf("{fd}\nNumber of iterations: = %d\n", \
			farm->out, farm->iter_len);
		else if (!ft_strcmp(av[i], "-l"))
			ft_printf("{fd}\nAlgorithm length: = %d\n", \
			farm->out, farm->algo_len);
		i++;
	}
	return (0);
}
