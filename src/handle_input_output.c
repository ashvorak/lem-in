/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_output.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 14:16:57 by oshvorak          #+#    #+#             */
/*   Updated: 2018/05/01 14:17:23 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

static void		put_fd(t_farm *farm, int i, char **av)
{
	int fd;

	if ((fd = open(av[i + 1], O_RDONLY)) != -1)
		farm->in = fd;
	else
		ft_usage();
}

void			handle_input_output(t_farm *farm, int ac, char **av)
{
	int i;

	i = 1;
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "-f"))
		{
			if (i + 1 < ac)
				put_fd(farm, i, av);
			else
				ft_usage();
		}
		else if (!ft_strcmp(av[i], "-o"))
		{
			if (i + 1 < ac)
				put_fd(farm, i, av);
			else
				ft_usage();
		}
		i++;
	}
}
