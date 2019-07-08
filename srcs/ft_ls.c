/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 19:11:23 by jsauron           #+#    #+#             */
/*   Updated: 2019/07/08 14:51:40 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	stop_exec(char *msg)
{
	printf("%s\n", msg);
	exit(0);
}

int		get_info(char *path, struct dirent *dirent, struct stat statbuf)
{
	if (S_ISREG(statbuf.st_mode)/* && ft_strcmp(path, dirent->d_name) == 0*/)
	{
		printf("Type: Fichier\n");
		printf("Mode: %s\n", ft_strmode(statbuf.st_mode));
		printf("Nombre de liens: %hu\n", statbuf.st_nlink);
	//	printf("Proprietaire: %d\n", getuid(statbuf.st_uid));
	//	printf("Groupe: %u\n", getgrgid(statbuf.st_gid));
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

//int		list_dir()

void	parse(char *path)
{
	DIR				*dir;
	struct dirent	*dirent;
	struct stat		statbuf;
	//char			current_path[PATH_MAX];

	//ouvrir le current dir
	if ((dir = opendir(".")) == NULL)
			stop_exec(strerror(errno));
	//stocker le path du current file dans statbuf
	//if ((getcwd(current_path, PATH_MAX) == NULL))
	//		stop_exec(strerror(errno));
	//printf("curr->path = %s\n", current_path);
	if (stat( path, &statbuf) == -1)
			stop_exec(strerror(errno));
	if (S_ISDIR(statbuf.st_mode)/* && ft_strcmp(path, dirent->d_name) == 0*/)
		list_dir(path, dirent, dir, statbuf);
	if (S_ISREG(statbuf.st_mode)/* && ft_strcmp(path, dirent->d_name) == 0*/)
		get_info(path, dirent, statbuf);;
	closedir(dir);
}

int		main(int ac, char **av)
{
	//parsing
	if (ac == 1)
		parse(".");
	else if (ac > 1)
		parse(av[1]);
	return (0);
}
