#include "../inc/lem_in.h"

static void ft_free_arr_int(int **arr, int size)
{
	int i;

	i = 0;
	if (arr)
	{
		while (i < size)
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}

static void free_rooms(t_room *room)
{
	t_room *tmp;

	while (room)
	{
		ft_strdel(&room->name);
		tmp = room;
		room = room->next;
		free(tmp);
	}
}

void free_farm(t_farm *farm)
{
	t_path *tmp;
	t_path *buf;

	tmp = farm->head_path;
	ft_strdel(&farm->map);
	ft_free_arr_int(farm->connects, farm->size);
	ft_free_arr_int(farm->paths, farm ->size);
	free_rooms(farm->head_room);
	while (tmp)
	{
		//free_rooms(tmp->head_room);
		buf = tmp;
		tmp = tmp->next;
		free(buf);
	}
}
