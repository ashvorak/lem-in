/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 17:40:03 by oshvorak          #+#    #+#             */
/*   Updated: 2018/04/11 17:35:59 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>
# include "../lib/libft.h"
# include "../lib/get_next_line/get_next_line.h"
# include "../lib/ft_printf/inc/ft_printf.h"

typedef enum	e_comment
{
	comment = 1,
	start,
	end
}				t_comment;

typedef struct	s_room
{
	int				id;
	char			*name;
	int				x;
	int				y;
	int 			is_ant;
	int 			is_way;
	struct s_room	*next;
}				t_room;

typedef struct	s_path
{
	int 			ants;
	t_room			*head_room;
	struct s_room	*next;
}				t_path;

typedef struct	s_farm
{
	int		ants;
	t_room	*head_room;
	int 	size;
	int		**connects;
	int 	**paths;
	t_path	*head_path;
	int		start_id;
	int		end_id;
	
}				t_farm;

void	ft_error(void);

int		is_integer(char *str);
int		is_room(char *line);
int		is_command(char *line);
int		is_name(char *str, t_farm *farm);
int		is_connection(char *line, t_farm *farm);

void	read_rooms(int fd, t_farm *farm, char **line);
void	read_connections(int fd, t_farm *farm, char **line);
int		farm_size(t_farm *farm);
int		**ret_matrix(t_farm *farm);

t_room	*new_room(int id, char *name, int x, int y);

void	wave_tracing(t_farm *farm);
void	handle_ways(t_farm *farm);

int		farm_size(t_farm *farm);

#endif
