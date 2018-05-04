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
	exit(1);
}

void			ft_usage(void)
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
	farm->algo_len = 0;
	farm->iter_len = 0;
	farm->color = 0;
	farm->in = 0;
	farm->out = 1;
	return (farm);
}

int				main(int ac, char **av)
{
	char	*line;
	t_farm	*farm;

	farm = new_farm();
	handle_input_output(farm, ac, av);
	valid_flags(ac, av);
	if (get_next_line(farm->in, &line) == -1)
		ft_error();
	is_integer(line) ? farm->ants = ft_atoi(line) : ft_error();
	ft_strdel(&line);
	read_rooms(farm, &line);
	(farm->start_id == -1 || farm->end_id == -1) ? ft_error() : 0;
	read_connections(farm, &line);
	handle_path(farm);
	handle_flags_before(farm, ac, av);
	print_paths(farm);
	handle_flags_after(farm, ac, av);
	free_farm(farm);
	return (0);
}
