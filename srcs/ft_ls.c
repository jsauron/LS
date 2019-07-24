/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 19:11:23 by jsauron           #+#    #+#             */
/*   Updated: 2019/07/24 18:21:11 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	stop_exec(char *msg)
{
	printf("%s\n", msg);
	exit(0);
}

int		get_info(t_info *f, struct stat statbuf)
{
	//		printf("file = %s, %s\n", dirent->d_name, ft_strmode(statbuf.st_mode));
	if (S_ISREG(statbuf.st_mode)/* && ft_strcmp(path, dirent->d_name) == 0*/)
	{
		//		printf("Type: Fichier\n");
		//f->mode = ft_strmode(statbuf.st_mode);
		f->nb_lien =  statbuf.st_nlink;
		f->user = (getpwuid(statbuf.st_uid))->pw_name;
		f->gr_user = (getgrgid(statbuf.st_gid))->gr_name;
		f->size = statbuf.st_size;
		f->time = ctime(&statbuf.st_mtime);
	}
	return (1);
}

int		print_info(struct stat statbuf)
{
		//printf("Mode: %s\n", ft_strmode(statbuf.st_mode));
		printf("Nombre de liens: %hu\n", statbuf.st_nlink);
		printf("Proprietaire: %s\n", (getpwuid(statbuf.st_uid))->pw_name);
		printf("Groupe: %s\n", (getgrgid(statbuf.st_gid))->gr_name);
		printf("Taille: %lld octets\n", statbuf.st_size);
		printf("Date de derniere modification:: %s \n", ctime(&statbuf.st_mtime));
	return (1);
}

int		list_dir(struct dirent *dirent, DIR *dir, struct stat statbuf)
{
	if (S_ISDIR(statbuf.st_mode) /*&& ft_strcmp(path, dirent->d_name) == 0*/)
	{
		while ((dirent = readdir(dir)) != NULL)
			if ( (ft_strcmp(dirent->d_name, ".") != 0) && (ft_strcmp(dirent->d_name, "..") != 0))
				printf("%s\n", dirent->d_name);
	}
	return (1);
}


void	parse(char *path)
{
	DIR				*dir;
	struct dirent	*dirent;
	struct stat		statbuf;
	//char			current_path[PATH_MAX];

	//stocker le path du current file dans statbuf
	//if ((getcwd(current_path, PATH_MAX) == NULL))
	//		stop_exec(strerror(errno));
	dirent = NULL;
	if (lstat(path, &statbuf) == -1)
		stop_exec(strerror(errno));
	if (S_ISDIR(statbuf.st_mode) && ft_strcmp(path, dirent->d_name) == 0)
	{
		if ((dir = opendir(path)) == NULL)
			stop_exec(strerror(errno));
		list_dir(dirent, dir, statbuf);
		closedir(dir);
	}
	if (S_ISREG(statbuf.st_mode) && ft_strcmp(path, dirent->d_name) == 0)
		print_info(statbuf);;
}
/*
int   fonction_r(t_dir *curr, struct stat statbuf, struct dirent *dirent, DIR *dir, char *path)
{	

	t_dir   *new;


	if ((!(new = malloc(sizeof(t_dir)))) || (!(new->file = malloc(sizeof(t_file)))))
		stop_exec("malloc curr next in fonction_r failed");
	curr->next  = new;
	new->next = NULL;
	curr = curr->next;
	if (lstat(path, &statbuf) == -1)
		stop_exec(strerror(errno));
	if (S_ISDIR(statbuf.st_mode) && ft_strcmp(path, dirent->d_name) == 0)
	{
		if ((dir = opendir(path)) == NULL)
			stop_exec(strerror(errno));
	}
	write(1, C_CYAN, 5);
	write(1, C_BOLD, 5);
	printf("%s\n", path);
	write(1, C_NONE, 5);
	create_list(path, dirent, dir, curr);
	closedir(dir);

	//else if (S_ISREG(statbuf.st_mode))
	//	printf("%s\n", path);
	return (1);
}*/

int		listing_dir_all(char *path, t_element *curr)
{
		DIR				*dir;
		struct dirent	*dirent;
		struct stat statbuf;

		dir = NULL;
		dirent = NULL;

		printf(" %s\n", path);
		if (lstat(path, &statbuf) == -1)
			stop_exec(strerror(errno));
		if (S_ISDIR(statbuf.st_mode)/* && ft_strcmp(path, dirent->d_name) == 0*/)
			if ((dir = opendir(path)) == NULL)
				stop_exec(strerror(errno));

		read_all(curr, path, dirent, dir, statbuf);
		closedir(dir);

		check_dir(curr->head, curr);
		return (1);
}


int		main(int ac, char **av)
{
	//char	arg[5]  = {'l', 'R', 'a', 'r', 't'};
	//int (*flag[2])(char*, struct dirent *dirent, DIR *, struct stat*) = {list_dir, create_list};
	if (ac == 1)
		parse(".");
	else if (ft_strcmp(av[1], "-R") == 0)
	{
	if (ac < 3)
			listing_dir_all(".", init_list("."));
		else if (ac == 3)
			listing_dir_all(av[2], init_list(av[2]));
	}
	else if (ac > 1)
		parse(av[1]);

	return (0);
}
