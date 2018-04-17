#include "../inc/lem_in.h"

int	farm_size(t_farm *farm)
{
	int		size;
	t_room	*tmp;

	size = 0;
	tmp = farm->head_room;
	while (tmp)
	{
		tmp = tmp->next;
		size++;
	}
	return (size);
}

int	 ret_id(t_farm *farm, char *name)
{
	int 	id;
	t_room	*tmp;

	id = -1;
	tmp = farm->head_room;
	while (tmp)
	{
		if (!ft_strcmp(name, tmp->name))
			return (tmp->id);
		tmp = tmp->next;
	}
	return (id);
}

int **ret_matrix(t_farm *farm)
{
	int i;
	int j;
	int size;
	int **connects;

	i = 0;
	size = farm_size(farm);
	if (!(connects = (int**)malloc(sizeof(int*) * size)))
		exit(1);
	while (i < size)
	{
		if (!(connects[i] = (int*)malloc(sizeof(int) * size)))
			exit(1);
		j = 0;
		while (j < size)
			connects[i][j++] = 0;
		i++;
	}
	return (connects);
}

void	read_connections(int fd, t_farm *farm, char **line)
{
	int 	x;
	int 	y;
	int		**connects;
	char 	**arr;

	connects = ret_matrix(farm);
	do
	{
		if (is_connection(*line, farm) || is_command(*line))
		{
			if (is_connection(*line, farm))
			{
				arr = ft_strsplit(*line, '-');
				x = ret_id(farm, arr[0]);
				y = ret_id(farm, arr[1]);
				connects[x][y] = 1;
				connects[y][x] = 1;
			}
		}
		else
			ft_error();
	} while (get_next_line(fd, line));
	farm->connects = connects;
}

