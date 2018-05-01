/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 14:17:02 by oshvorak          #+#    #+#             */
/*   Updated: 2018/05/01 14:17:24 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void	map_join(t_farm *farm, char *line)
{
	char *buf;
	char *tmp;

	if (farm->map)
	{
		buf = ft_strdup(farm->map);
		ft_strdel(&farm->map);
		tmp = ft_strjoin(line, "\n");
		farm->map = ft_strjoin(buf, tmp);
		ft_strdel(&buf);
		ft_strdel(&tmp);
	}
	else
		farm->map = ft_strjoin(line, "\n");
	ft_strdel(&line);
}
