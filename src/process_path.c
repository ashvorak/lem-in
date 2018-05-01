#include "../inc/lem_in.h"

void		allocation_ants(t_farm *farm)
{
	int 	ants;
	t_path	*tmp;

	ants = farm->ants;
	tmp = farm->head_path;
	while (ants)
	{
		while (tmp->next)
		{
			if (tmp->length + tmp->ants < tmp->next->length + tmp->next->ants)
			{
				tmp->ants++;
				break ;
			}
			tmp = tmp->next;
		}
		if (!tmp->next)
			tmp->ants++;
		tmp = farm->head_path;
		ants--;
	}
}

t_room		*copy_room(t_room *room)
{
	t_room *copy;

	copy = new_room(room->id, ft_strdup(room->name), room->x, room->y);
	return (copy);
}

void		clean_connect(t_farm *farm, int id)
{
	int i;
	int j;

	i = 0;
	while (i < farm->size)
	{
		j = 0;
		while (j < farm->size)
		{
			if (i == id || j == id)
			{
				farm->connects[i][j] = 0;
				farm->connects[j][i] = 0;
			}
			j++;
		}
		i++;
	}
}

int 		find_min(t_farm *farm, int id)
{
	int j;
	int min;
	int tmp;

	j = 0;
	min = -1;
	tmp = 0;
	while (j < farm->size)
	{
		if (farm->paths[id][j] && (tmp > farm->paths[id][j] || min == -1))
		{
			min = j;
			tmp = farm->paths[id][j];
		}
		j++;
	}
	return (min);
}

int			path_length(t_path *path)
{
	int		size;
	t_room	*tmp;

	size = 0;
	tmp = path->head_room;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}


