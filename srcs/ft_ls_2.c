/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 17:03:59 by jsauron           #+#    #+#             */
/*   Updated: 2019/07/24 18:19:52 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_element		*init_list(char *path)
{
	t_element	*curr;

	(curr = malloc(sizeof(t_element))) == NULL ? stop_exec("malloc curr failed") : 0;
	(curr->info = malloc(sizeof(t_info))) == NULL ? stop_exec("malloc info failed") : 0;	

	curr->head = curr;
	curr->name = path;
	curr->path = path;
	curr->next = NULL;
	curr->stair = 0;
	return (curr);
}

t_element			*read_all(t_element *curr, char *path, struct dirent *dirent, DIR *dir, struct stat statbuf)
{
	t_element	*new;
	int static i;
	char *new_path;

	i++;
	while ((dirent = readdir(dir)) != NULL)
	{
		if ((ft_strcmp(dirent->d_name, ".") != 0) && (ft_strcmp(dirent->d_name, "..") != 0) && *dirent->d_name != '.')
		{
			(new = malloc(sizeof(t_element))) == NULL ? stop_exec("malloc new failed") : 0;
			(new->info = malloc(sizeof(t_info))) == NULL ? stop_exec("malloc info failed") : 0;
			curr->next = new;
			new->next = NULL;
			new->head = curr->head;
			curr = curr->next;

			new_path = ft_addstr(path, ft_addstr("/", dirent->d_name));
			lstat(new_path ,&statbuf);

			curr->state = (S_ISDIR(statbuf.st_mode) ? 1 : 0);

			curr->path = new_path;
			curr->name = ft_strdup(dirent->d_name);
      get_info(curr->info, statbuf);
 /*    if (curr->state)
			  printf("\033[36m \033[1m %s\t \033[0m", curr->name);
      else
			  printf("%s\t",curr->name);
	*/		curr->stair = i;
		}
	}
 //   printf("\n");
	return (curr);
}

int			check_dir(t_element *head, t_element *curr, t_flag *flag)
{
  t_element *elem;

  elem = head;
	while (elem != NULL)
	{
		if (elem->state == 1)
		{
     // printf("\n%s:\n", elem->path);
			elem->state = 0;
			listing_dir_all(elem->path, curr, flag);
    }
		elem = elem->next;
	}
	return (1);
}

