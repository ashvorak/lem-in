#include "../inc/lem_in.h"

static t_path *new_path()
{
	t_path *path;

	if (!(path = (t_path*)malloc(sizeof(t_path))))
		return (NULL);
	path->id = NULL;
	path->next = NULL;
	return (path);
}

static int make_path(t_farm *farm, int index)
{
	while ()
	{

	}
}

void handle_ways(t_farm *farm)
{
	t_path *path;

	path = make_path(farm, farm->end_id);
}
