#include "../inc/lem_in.h"

static int move(t_path *path, t_farm *farm)
{
	int		ant;
	t_room	*tmp;

	ant = path->first_ant + path->ants_end;
	tmp = path->head_room;
	if (path->ants_start != path->ants_end)
	{
		while (tmp->next)
		{
			if (tmp->next->is_ant)
			{
				ft_printf("L%d-%s ", ant, tmp->name);
				tmp->is_ant = 1;
				tmp->next->is_ant = 0;
				(tmp->id == farm->end_id) ? path->ants_end++ : 0;
				ant++;
			}
			tmp = tmp->next;
		}
		if (path->ants_go != path->ants_start)
		{
			ft_printf("L%d-%s ", ant, tmp->name);
			path->ants_go++;
			tmp->is_ant = 1;
		}
	}
	return (path->ants_end);
}

void print_paths(t_farm *farm)
{
	int 	ants_finish;
	t_path	*tmp;

	ants_finish = 0;
	while (ants_finish != farm->ants)
	{
		ants_finish = 0;
		tmp = farm->head_path;
		while (tmp)
		{
			ants_finish += move(tmp, farm);
			tmp = tmp->next;
		}
		ft_printf("\n");
	}
}