/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 14:23:38 by oshvorak          #+#    #+#             */
/*   Updated: 2018/04/12 12:02:51 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

int	is_integer(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	is_room(char *line)
{
	int		i;
	char	**arr;

	i = 0;
	arr = ft_strsplit(line, ' ');
	while (arr[i])
	{
		if (!is_integer(arr[i]) && i != 0)
		{
			ft_free_arr(arr);
			return (0);
		}
		else if (i == 0 && (arr[i][0] == 'L' || arr[i][0] == '#'))
		{
			ft_free_arr(arr);
			return (0);
		}
		i++;
	}
	ft_free_arr(arr);
	return (i == 3 ? 1 : 0);
}

int	is_command(char *line)
{
	if (line[0] == '#')
	{
		if (ft_strstr(line, "##start"))
			return (start);
		else if (ft_strstr(line, "##end"))
			return (end);
		else
			return (comment);
	}
	return (0);
}

int	is_name(char *str, t_farm *farm)
{
	t_room *tmp;

	tmp = farm->head_room;
	while (tmp)
	{
		if (!ft_strcmp(str, tmp->name))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	is_connection(char *line, t_farm *farm)
{
	int		res;
	char	**arr;

	arr = ft_strsplit(line, '-');
	if (ft_array_size(arr) != 2)
		res = 0;
	else if (!ft_strcmp(arr[0], arr[1]))
		res = 0;
	else if (!is_name(arr[0], farm) || !is_name(arr[1], farm))
		res = 0;
	else
		res = 1;
	ft_free_arr(arr);
	return (res);
}
