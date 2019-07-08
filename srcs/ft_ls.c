/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 19:11:23 by jsauron           #+#    #+#             */
/*   Updated: 2019/07/08 18:17:41 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	stop_exec(char *msg)
{
	printf("%s\n", msg);
	exit(0);
}

int		get_info_in_list(t_info *f, char *path, struct dirent *dirent, struct stat statbuf)
{
		printf("%s\n", ft_strmode(statbuf.st_mode));
	if (S_ISREG(statbuf.st_mode)/* && ft_strcmp(path, dirent->d_name) == 0*/)
	{
		printf("Type: Fichier\n");
		f->mode = ft_strmode(statbuf.st_mode);
		f->nb_lien =  statbuf.st_nlink;
		f->user = (getpwuid(statbuf.st_uid))->pw_name;
		f->gr_user = (getgrgid(statbuf.st_gid))->gr_name;
		f->size = statbuf.st_size;
		f->time = ctime(&statbuf.st_mtime);
	}
	return (1);
}

int		get_info(char *path, struct dirent *dirent, struct stat statbuf)
{
	if (S_ISREG(statbuf.st_mode)/* && ft_strcmp(path, dirent->d_name) == 0*/)
	{
		printf("Type: Fichier\n");
		printf("Mode: %s\n", ft_strmode(statbuf.st_mode));
		printf("Nombre de liens: %hu\n", statbuf.st_nlink);
		printf("Proprietaire: %s\n", (getpwuid(statbuf.st_uid))->pw_name);
		printf("Groupe: %s\n", (getgrgid(statbuf.st_gid))->gr_name);
		printf("Taille: %lld octets\n", statbuf.st_size);
		printf("Date de derniere modification:: %s \n", ctime(&statbuf.st_mtime));
	}
	return (1);
}

int		list_dir(char *path, struct dirent *dirent, DIR *dir, struct stat statbuf)
{
	if (S_ISDIR(statbuf.st_mode) /*&& ft_strcmp(path, dirent->d_name) == 0*/)
	{
		while ((dirent = readdir(dir)) != NULL)
		{
			if ( (ft_strcmp(dirent->d_name, ".") != 0) && (ft_strcmp(dirent->d_name, "..") != 0)) //skip les fichier cacher
				printf("%s\n", dirent->d_name);
		}
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
	if (lstat(path, &statbuf) == -1)
		stop_exec(strerror(errno));
	if (S_ISDIR(statbuf.st_mode)/* && ft_strcmp(path, dirent->d_name) == 0*/)
	{
		if ((dir = opendir(path)) == NULL)
			stop_exec(strerror(errno));
		list_dir(path, dirent, dir, statbuf);
		closedir(dir);
	}
	if (S_ISREG(statbuf.st_mode)/* && ft_strcmp(path, dirent->d_name) == 0*/)
		get_info(path, dirent, statbuf);;
}

int		fonction_r(char *path)
{
	DIR				*dir;
	struct dirent	*dirent;
	struct stat		statbuf;
	
	if (lstat(path, &statbuf) == -1)
		stop_exec(strerror(errno));
	if (S_ISDIR(statbuf.st_mode)/* && ft_strcmp(path, dirent->d_name) == 0*/)
	{
		if ((dir = opendir(path)) == NULL)
			stop_exec(strerror(errno));
		create_list(path, dirent, dir, statbuf);
		//list_dir(path, dirent, dir, statbuf);
		closedir(dir);
	}
	return (1);
}


int		main(int ac, char **av)
{
	char	arg[5]  = {'l', 'R', 'a', 'r', 't'};
	//parsing
	if (ac == 1)
		parse(".");
	else if (ft_strcmp(av[1], "-R") == 0)
	{
		if (ac < 3) 
			fonction_r(".");
		else if (ac == 3)
			fonction_r(av[2]);
	}
	else if (ac > 1)
		parse(av[1]);

	return (0);
}
