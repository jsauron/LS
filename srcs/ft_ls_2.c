/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 17:03:59 by jsauron           #+#    #+#             */
/*   Updated: 2019/07/24 17:22:15 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char	*ft_addstr(char *s1, char *s2)
{
	char	*res;
	int i;
	int j;
	int len;

	j = 0;
	i = 0;
	res = NULL;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	res = malloc(sizeof(char) * len);
	while ( s1 && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while ( s2 && s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
}

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

int			read_all(t_element *curr, char *path, struct dirent *dirent, DIR *dir, struct stat statbuf)
{
	t_element	*new;
	int static i;
	char *new_path;

	i++;
	while ((dirent = readdir(dir)) != NULL)
	{

		if ((ft_strcmp(dirent->d_name, ".") != 0)&& (ft_strcmp(dirent->d_name, "..") != 0))
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
			curr->path = path;
			//printf("%s\n",curr->path);
			curr->name = dirent->d_name;
			printf("%s\n",curr->name);
			curr->stair = i;
		}
	}
	curr = curr->head;
	return (1);
}

int			check_dir(t_element *head)
{
	head = head->next;
	while (head != NULL)
	{
		printf("%s\t", head->name);
		head = head->next;
	}
	return (1);
}


/*
   t_dir		*create_list(char *path, struct dirent *dirent, DIR *dir, t_dir *curr)
   {
   struct stat		stat_b;
   char	*new_path;
   t_dir   *new;
   new_path = NULL;
   while ((dirent = readdir(dir)) != NULL)
   {
   if ((ft_strcmp(dirent->d_name, ".") != 0) && (ft_strcmp(dirent->d_name, "..") != 0))
   {
   new_path = ft_addstr(path, ft_addstr("/", dirent->d_name));
   lstat(new_path ,&stat_b);
   if (S_ISDIR(stat_b.st_mode))
   add_dir(curr, stat_b,  dirent, new_path, dir);
   else if (S_ISREG(stat_b.st_mode))
   printf("%s\t", dirent->d_name );
//add_file(curr, stat_b, dirent->d_name, new_path);
if ((!(new = malloc(sizeof(t_dir)))) || (!(new->file = malloc(sizeof(t_file)))))
stop_exec("malloc curr next in fonction_r failed");
curr->next  = new;
new->next = NULL;
curr = curr->next;
}
}
curr->next = NULL;
return (curr);
}*/
