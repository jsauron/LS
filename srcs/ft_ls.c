/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 19:11:23 by jsauron           #+#    #+#             */
/*   Updated: 2019/08/08 22:22:52 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		get_info(t_info *f, struct stat statbuf)
{
	f->mode = ft_strdup(ft_strmode(statbuf.st_mode));
	f->nb_lien =  statbuf.st_nlink;
	f->user = ft_strdup((getpwuid(statbuf.st_uid))->pw_name);
	f->gr_user = ft_strdup((getgrgid(statbuf.st_gid))->gr_name);
	f->size = statbuf.st_size;
	f->time = statbuf.st_mtimespec.tv_sec;
	f->str_time = ft_strdup(ctime(&statbuf.st_mtime));
	f->type = (S_ISDIR(statbuf.st_mode)) ? 1 : 0;
	return (1);
}

int		print_info(t_flag *flag,t_element *curr, t_info *f)
{
	add_to_buff(flag, f->mode);
	add_to_buff(flag, ft_itoa((int)f->nb_lien));
	add_to_buff(flag, f->user);
	add_to_buff(flag, f->gr_user);
	add_to_buff(flag, ft_itoa((int)f->size));
	add_to_buff(flag, f->str_time);
	add_to_buff(flag, curr->name);
	return (1);
}

t_element		*listing_dir_all(char *path, t_element *curr, t_flag *flag)
{
	DIR				*dir;
	struct stat statbuf;

	dir = NULL;
	if (lstat(path, &statbuf) == -1)
	{
		printf("ls: %s: %s\n", path,  (strerror(errno)));
		return (curr);
	}
	if (S_ISDIR(statbuf.st_mode))
	{
		(dir = opendir(path)) ? 0 : printf("ls: %s: %s\n", path,  (strerror(errno)));
		curr = read_all(flag, curr, path, dir, statbuf);
		sort_list(flag, curr->head->next);
		if ((flag->ac > 2 || flag->r) && ft_strcmp(path, ".") != 0)
		{
			add_to_buff(flag, "\n");
			add_to_buff(flag, path);
			add_to_buff(flag, ":\n");
		}
		print_list(flag, curr->head);
		(flag->r) ? check_dir(curr->head, curr, flag) : 0;
		closedir(dir);
	}
	else
	{
		curr = add_node(curr, path, path, statbuf, 0);
		print_list(flag, curr->head);
	}
	return (curr);
} 

t_element		*ls_file(t_flag *flag)
{
	int i;
	t_element *list;

	i = 0;
	list = NULL;
	while (flag->file[i])
	{
		list = init_list(*flag->file);
		list = listing_dir_all(flag->file[i], list, flag);
		//free_list(list);
		i++;
	}
	return (list->head);
}

int		main(const int ac, char *av[])
{
	t_flag    flag;

	if (!parse(&flag, ac, av))
		return (0);
	sort_file(&flag);
	ls_file(&flag);
	ft_putstr((char const *)flag.buf);
	free(flag.file);
	free(flag.sort);
	return (0);
}

