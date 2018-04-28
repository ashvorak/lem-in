#include "../inc/lem_in.h"

static t_path	*new_path(t_room *room)
{
	t_path *path;

	if (!(path = (t_path*)malloc(sizeof(t_path))))
		return (NULL);
	path->first_ant = 0;
	path->ants = 0;
	path->ants_go = 0;
	path->ants_finish = 0;
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
			{
				farm->connects[i][j] = 0;
				farm->connects[j][i] = 0;
			}
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
	t_room	*tmp;
	t_room	*head_room;
	t_path	*path;

	id_way = farm->end_id;
	head_room = copy_room(ret_room(farm, farm->end_id));
	tmp = head_room;
	while (id_way != farm->start_id)
	{
		if ((id_min = find_min(farm, id_way)) == -1)
			return (NULL);
		if (id_min != farm->start_id)
		{
			room = copy_room(ret_room(farm, id_min));
			tmp->next = room;
			tmp = room;
		}
		if (id_way != farm->end_id)
			clean_connect(farm, id_way);
		else if (id_way == farm->end_id && id_min == farm->start_id)
		{
			farm->connects[farm->start_id][farm->end_id] = 0;
			farm->connects[farm->end_id][farm->start_id] = 0;
		}
		id_way = id_min;
	}
	path = new_path(head_room);
	return (path);
}

void allocation_ants(t_farm *farm)
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

int path_length(t_path *path)
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

void handle_ways(t_farm *farm)
{
	t_room	*tmp;
	t_path	*buf;
	t_path	*path;

	while ((path = make_path(farm)))
	{
		if (!farm->head_path)
		{
			farm->head_path = path;
			buf = path;
		}
		else
		{
			buf->next = path;
			buf = path;
		}
		path->length = path_length(path);
		wave_tracing(farm);
	}
	(farm->head_path) ? allocation_ants(farm) : ft_error();
	buf = farm->head_path;
	while (buf)
	{
		tmp = buf->head_room;
		while (tmp)
		{
			ft_printf("%s ", tmp->name);
			tmp = tmp->next;
		}
		ft_printf("\nlen %d\n", buf->length);
		ft_printf("number %d\n", buf->ants);
		ft_printf("--------------------\n");
		buf = buf->next;
	}
}
