#include "../includes/ft_ls.h"

int   init_ptr_fct_sort(fcn *ftab)
{
	ftab[0] = &ascii; 
	ftab[1] = &time_modif; // -t
	ftab[2] = &reverse_ascii; // -r
	ftab[3] = &size; // -S
	//  ftab[4] = &not_sorted; // -f
	return (1);
}

/* 
   tab[1] = &get_info; // -l
   tab[2] = &show_hide; // -a
   tab[3] = &recursive; // -R
   tab[4] = &time; // -t
   ftab[5] = &reverse_alpha; // -r
   ftab[0] = &size; -S // 
   bjv ftab[0] = &not_sorted; // -f

   }
   */
int           sort_list(t_flag *flag, t_element *curr)
{
	if (!flag->r)
		sort_elem_by(curr, ascii);
	while (flag->sort && *flag->sort )
	{
		sort_elem_by(curr, flag->ftab[(int)*flag->sort]);
		flag->sort++;
	} 
	return (0);
}

void	swap_node(t_element *a, t_element *b)
{	
	char *tmp;
	char *tmp_path;
	t_info *tmp_info;

	tmp_path = a->path;
	tmp_info = a->info;
	tmp = a->name;

	a->path = b->path;
	a->info = b->info;
	a->name = b->name;

	b->path = tmp_path;
	b->info = tmp_info;
	b->name = tmp;
}

t_element     *sort_elem_by(t_element *curr, int(*sort)(struct t_element *, struct t_element *))
{
	t_element *head;

	head = curr;
	while (curr && curr->next)
	{
			if ((*sort)(curr, curr->next) != 0)
			{
				swap_node(curr, curr->next);
				curr = head;
			}
			else
				curr = curr->next;
	}
	curr = head;
	return (curr);
}

/*int   ascii_path(t_element *curr, t_element *next)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (curr->path[i]
	return(ft_strcmp(curr->path, next->path));
}
*/
int   ascii(t_element *curr, t_element *next)
{
	int i;

	i = 0;
	while (curr->name[i] - next->name[i] == 0) 
		i++;
	if (curr->name[i] - next->name[i] > 0)
		return (-1);
	return (0);
}

int   reverse_ascii(t_element *curr, t_element *next)
{
	int i;

	i = 0;
	while (curr->name[i] - next->name[i] == 0) 
		i++;
	if (curr->name[i] - next->name[i] < 0)
		return (-1);
	return (0);
}

int   size(t_element *curr, t_element *next)
{
	if (curr->info->size > next->info->size)
		return (-1);
	return (0);
} 

int   time_modif(t_element *curr, t_element *next)
{
	if (curr->info->time < next->info->time)
		return (-1);
	return (0);
}
