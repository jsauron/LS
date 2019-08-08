/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 13:38:02 by jsauron           #+#    #+#             */
/*   Updated: 2019/08/08 15:37:09 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int			sort_list(t_flag *flag, t_element *curr)
{
	if (!flag->r)
		sort_elem_by(curr, ascii);
	if (flag->sort && *flag->sort)
		sort_elem_by(curr, *flag->sort);
	return (0);
}

int		sort_file(t_flag *flag)
{
	int i;
	char	*tmp;
	char	**file;

	file = flag->file;
	tmp = NULL;
	i = 0;
	while (file[i + 1])
	{
		if (ft_strcmp(file[i], file[i + 1]) > 0)
		{
			tmp = file[i];
			file[i] = file[i + 1];
			file[i + 1] = tmp;
			i = 0;
		}
		else 
			i++;
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

t_element	*whos_next(t_element *d, int i)
{
	t_element *tmp;
	int j;

	j = 0;
	tmp = d;
	while (j < i && tmp != NULL)
	{
		printf("j = %d\n", j);
		tmp = tmp->next;
		j++;
	}
	printf("node swap 1= %s\n", d->name);
	printf("node swap 2= %s\n", tmp->name);
	return (tmp);
}

int		sort_column_list(t_flag *flag, t_element *d)
{
	int			i;
	t_element	*tmp;

	tmp = d;
	i = 0;
	while (d != NULL)
	{
		printf("%d\n", flag->nb_lign);
		if (i % flag->nb_lign == 0)
		{
			tmp = whos_next(d, i + flag->nb_col -1);
			swap_node(d, tmp);
		}
		d = d->next;
	}
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
	if (curr->info->size < next->info->size)
		return (-1);
	return (0);
} 

int   time_modif(t_element *curr, t_element *next)
{
	if (curr->info->time < next->info->time)
		return (-1);
	return (0);
}
