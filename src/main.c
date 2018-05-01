/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 12:59:41 by oshvorak          #+#    #+#             */
/*   Updated: 2018/04/11 17:35:52 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void			ft_error(void)
{
	ft_printf("ERROR\n");
	//free_farm(farm);
	exit(1);
}

static	void	ft_usage(void)
{
	ft_printf("Usage : ./lem-in <filename>\n");
	exit(1);
}

static t_farm	*new_farm(void)
{
	t_farm *farm;

	if (!(farm = (t_farm*)malloc(sizeof(t_farm))))
		return (NULL);
	farm->map = NULL;
	farm->ants = 0;
	farm->ant_id_go = 1;
	farm->head_room = NULL;
	farm->size = 0;
	farm->connects = NULL;
	farm->paths = NULL;
	farm->head_path = NULL;
	farm->start_id = -1;
	farm->end_id = -1;
	return (farm);
}

int				main(int ac, char **av)
{
	int		fd;
	char	*line;
	t_farm	*farm;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		farm = new_farm();
		if (get_next_line(fd, &line) == -1)
			ft_error();
		is_integer(line) ? farm->ants = ft_atoi(line) : ft_error();
		ft_strdel(&line);
		read_rooms(fd, farm, &line);
		(farm->start_id == -1 || farm->end_id == -1) ? ft_error() : 0;
		read_connections(fd, farm, &line);
		ft_printf("%s\n", farm->map);
		wave_tracing(farm);
		handle_path(farm);
		(farm->head_path) ? allocation_ants(farm) : ft_error();
		print_paths(farm);
		free_farm(farm);
	}
	else
		ft_usage();
	//system("leaks lem_in");
	return (0);
}
