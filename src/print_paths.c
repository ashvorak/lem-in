#include "../inc/lem_in.h"

static int go_way(t_path *path)
{
	t_room	*tmp;

	tmp = path->head_room;
	if (path->ants_start != path->ants_end)
	{
		while (tmp)
			tmp = tmp->next;
	}
	return (path->ants_end);
}

void print_paths(t_farm *farm)
{
	int 	ants_finish;
	t_path	*tmp;

	tmp = farm->head_path;
	while (ants_finish != farm->ants)
	{
		while (tmp)
		{
			ants_finish = go_way(tmp);
			tmp = tmp->next;
		}
	}
}
