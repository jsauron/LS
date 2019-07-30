/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 19:11:23 by jsauron           #+#    #+#             */
/*   Updated: 2019/07/29 19:00:33 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		get_info(t_info *f, struct stat statbuf)
{
	f->mode = ft_strdup(ft_strmode(statbuf.st_mode));
	f->nb_lien =  statbuf.st_nlink;
	f->user = ft_strdup((getpwuid(statbuf.st_uid))->pw_name);
	f->gr_user = (getgrgid(statbuf.st_gid))->gr_name;
	f->size = statbuf.st_size;
	f->time = statbuf.st_mtimespec.tv_sec;
	f->str_time = ctime(&statbuf.st_mtime);
	f->type = (S_ISDIR(statbuf.st_mode)) ? 1 : 0;
	return (1);
}

int		print_info(t_element *curr, t_info *f)
{
	printf("Total %d \n", f->nb_lien);
	printf("%s  ", f->mode);
	printf("%d ", f->nb_lien);
	printf("  %s  ", f->user);
	printf(" %s ", f->gr_user);
	printf(" %zu ", f->size);
	printf(" %s ", f->str_time);
	printf(" %s", curr->name);
	return (1);
}

t_element		*listing_dir_all(char *path, t_element *curr, t_flag *flag)
{
	DIR				*dir;
	struct stat statbuf;
  int       i;

	dir = NULL;
  i = 0;
  while (flag->file[i])
  {
    path = flag->file[i];
	(lstat(path, &statbuf) == -1) ? stop_exec(strerror(errno)) : 0;
	if (S_ISDIR(statbuf.st_mode))
	{
		(dir = opendir(path)) ? 0 : stop_exec(strerror(errno));
		curr = read_all(flag, curr, path, dir, statbuf);
		closedir(dir); 
		flag->r ? check_dir(curr->head, curr, flag) : 0;
	}
	else
    curr = add_node(curr, path, path, statbuf, 0);
  i++;
  } 
	sort_list(flag, curr->head->next); // avant curr->head->next
	return (curr->head);
}

int		main(const int ac, char *av[])
{
	int i;
	t_flag    flag;

	i = 0;
	if (!parse(&flag, ac, av))
		return (0);
		print_list(&flag, listing_dir_all(flag.file[0], init_list(*flag.file), &flag));
	return (0);
}

