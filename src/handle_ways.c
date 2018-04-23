#include "../inc/lem_in.h"

static t_path	*new_path(t_room *room)
{
	t_path *path;

	if (!(path = (t_path*)malloc(sizeof(t_path))))
		return (NULL);
	path->ants = 0;
	path->head_room = room;
	path->next = NULL;
	return (path);
}

static t_room	*ret_room(t_farm *farm, int id)
{
	t_room *tmp;

	tmp = farm->head_room;
	while (id != tmp->id)
		tmp = tmp->next;
	return (tmp);
}

static int 		find_min(t_farm *farm, int id)
{
	int j;
	int min;

	j = 0;
	min = -1;
	while (j < farm->size)
	{
		if (farm->paths[id][j] && (min > farm->paths[id][j] || min == -1))
			min = j;
		j++;
	}
	return (min);
}

static t_room	*copy_room(t_room *room)
{
	t_room *copy;

	copy = new_room(room->id, room->name, room->x, room->y);
	return (copy);
}

static void		clean_connect(t_farm *farm, int id)
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
				farm->paths[i][j] = 0;
			j++;
		}
		i++;
	}
}

static t_path	*make_path(t_farm *farm)
{
	int 	id_min;
	int 	id_way;
	t_room	*room;
	t_room	*head_room;
	t_path	*path;

	id_way = farm->end_id;
	head_room = copy_room(ret_room(farm, farm->end_id));
	while (id_way != farm->start_id)
	{
		id_min = find_min(farm, id_way);
		room = copy_room(ret_room(farm, id_min));
		room->next = head_room;
		head_room = room;
		id_way != farm->end_id ? clean_connect(farm, id_way) : 0;
		id_way = id_min;
	}
	path = new_path(head_room);
	return (path);
}

void handle_ways(t_farm *farm)
{
	t_room	*tmp;
	t_path	*path;

	path = make_path(farm);
	tmp = path->head_room;
	while (tmp)
	{
		ft_printf("%s\n", tmp->name);
		tmp = tmp->next;
	}
}
