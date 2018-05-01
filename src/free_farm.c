/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_farm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 14:16:54 by oshvorak          #+#    #+#             */
/*   Updated: 2018/05/01 14:17:23 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void	free_rooms(t_room *room)
{
	t_room *tmp;

	while (room)
	{
		ft_strdel(&room->name);
		tmp = room;
		room = room->next;
		free(tmp);
	}
}

void	free_farm(t_farm *farm)
{
	t_path *tmp;
	t_path *buf;

	tmp = farm->head_path;
	ft_strdel(&farm->map);
	ft_free_arr_int(farm->connects, farm->size);
	ft_free_arr_int(farm->paths, farm->size);
	free_rooms(farm->head_room);
	while (tmp)
	{
		free_rooms(tmp->head_room);
		buf = tmp;
		tmp = tmp->next;
		free(buf);
	}
	free(farm);
}
