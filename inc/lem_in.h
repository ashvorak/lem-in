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
	int 			ant_id;
	struct s_room	*next;
}				t_room;

typedef struct	s_path
{
	int 			ants;
	int 			ants_go;
	int 			ants_finish;
	int 			length;
	t_room			*head_room;
	struct s_path	*next;
}				t_path;

typedef struct	s_farm
{
	int		ants;
	int		ant_id_go;
	char	*map;
	t_room	*head_room;
	int 	size;
	int		**connects;
	int 	**paths;
	t_path	*head_path;
	int		start_id;
	int		end_id;
	int 	algo_len;
	int 	iter_len;
	int 	color;
	int 	in;
	int 	out;
}				t_farm;

void			ft_error(void);
void			ft_usage(void);

int				is_integer(char *str);
int				is_room(char *line);
int				is_command(char *line);
int				is_name(char *str, t_farm *farm);
int				is_connection(char *line, t_farm *farm);

void			read_rooms(t_farm *farm, char **line);
void			read_connections(t_farm *farm, char **line);
int				**ret_matrix(t_farm *farm);

t_room			*new_room(int id, char *name, int x, int y);
void			allocation_ants(t_farm *farm);
t_room			*copy_room(t_room *room);
int				find_min(t_farm *farm, int id);
int				path_length(t_path *path);
void			clean_connect(t_farm *farm, int id);
t_room			*ret_room(t_farm *farm, int id);

void			wave_tracing(t_farm *farm);
void			handle_path(t_farm *farm);
void			print_paths(t_farm *farm);
void			map_join(t_farm *farm, char *line);
void			free_rooms(t_room *room);
void			free_farm(t_farm *farm);

int				handle_flags_before(t_farm *farm, int ac, char **av);
int				handle_flags_after(t_farm *farm, int ac, char **av);
void			handle_input_output(t_farm *farm, int ac, char **av);
int				valid_flags(int ac, char **av);

#endif
