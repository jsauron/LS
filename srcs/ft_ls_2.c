/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 17:03:59 by jsauron           #+#    #+#             */
/*   Updated: 2019/08/05 21:04:10 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_element		*init_list(char *path)
{
	t_element	*curr;

	(curr = malloc(sizeof(t_element))) == NULL ? stop_exec("malloc curr failed") : 0;
	(curr->info = malloc(sizeof(t_info))) == NULL ? stop_exec("malloc info failed") : 0;	
	ft_bzero(curr->info, sizeof(t_info));
	curr->head = curr;
	curr->name = path;
	curr->path = path;
	curr->next = NULL;
	return (curr);
}

t_element			*add_node(t_element *curr, char *path, char *name, struct stat statbuf, int i)
{
	t_element	*new;
	char *new_path;
	
	(new = malloc(sizeof(t_element))) == NULL ? stop_exec("malloc new failed") : 0;
	(new->info = malloc(sizeof(t_info))) == NULL ? stop_exec("malloc info failed") : 0;
	curr->next = new;
	new->next = NULL;
	new->head = curr->head;
	curr = curr->next;

	ft_bzero(curr->info, sizeof(t_info));
	new_path =  ft_addstr(path, ft_addstr("/", name));
	lstat(new_path ,&statbuf);

	curr->info->state = (S_ISDIR(statbuf.st_mode) ? 1 : 0);

	curr->path = new_path;
	curr->name = ft_strdup(name);
	get_info(curr->info, statbuf);
	curr->info->stair = i;
	return (curr);
}

t_element			*read_all(t_flag *flag, t_element *curr, char *path,  DIR *dir, struct stat statbuf)
{
	struct	dirent *dirent;
	int static i;
	t_element *head;

	head = curr;
	dirent = NULL;
	i++;
	while ((dirent = readdir(dir)) != NULL)
	{
		if (flag->a)
			curr = add_node(curr, path, dirent->d_name, statbuf, i);
		else if ((ft_strcmp(dirent->d_name, ".") != 0)
				&& (ft_strcmp(dirent->d_name, "..") != 0)
				&& *dirent->d_name != '.')
			curr = add_node(curr, path, dirent->d_name, statbuf, i);
	}
	return (head);
}

int			check_dir(t_element *head, t_element *curr, t_flag *flag)
{
	t_element *elem;

	elem = head->next;
	while (elem != NULL)
	{
		if (elem->info->state == 1  && ft_strcmp(elem->name, "..") != 0 && ft_strcmp(elem->name, ".") != 0)
		{
			elem->info->state = 0;
			listing_dir_all(elem->path, curr, flag);;
		}
		elem = elem->next;
	}
	return (1);
}

