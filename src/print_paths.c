#include "../inc/lem_in.h"

static int move(t_path *path, t_farm *farm, int ant_num)
{
	int		ant;
	t_room	*tmp;

	ant = path->first_ant + path->ants_finish;
	tmp = path->head_room;
	ant_num -= path->ants - path->ants_finish;
	if (path->ants != path->ants_finish)
	{
		while (tmp->next)
		{
			if (tmp->next->is_ant)
			{
				ft_printf("L%d-%s ", ant_num++, tmp->name);
				tmp->is_ant = 1;
				tmp->next->is_ant = 0;
				(tmp->id == farm->end_id) ? path->ants_finish++ : 0;
				ant++;
			}
			tmp = tmp->next;
		}
		if (path->ants_go != path->ants)
		{
			ft_printf("L%d-%s ", ant_num, tmp->name);
			path->ants_go++;
			tmp->is_ant = 1;
		}
	}
	return (path->ants_finish);
}

void print_paths(t_farm *farm)
{
	int 	ants_finish;
	int 	ant_num;
	t_path	*tmp;

	ants_finish = 0;
	ant_num = 1;
	while (ants_finish != farm->ants)
	{
		ants_finish = 0;
		tmp = farm->head_path;
		ant_num = 1;
		while (tmp)
		{
			ant_num += tmp->ants;
			ants_finish += move(tmp, farm, ant_num);
			tmp = tmp->next;
		}
		ft_printf("\n");
	}
}
