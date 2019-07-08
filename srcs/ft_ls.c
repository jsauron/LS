/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 19:11:23 by jsauron           #+#    #+#             */
/*   Updated: 2019/07/08 11:54:48 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	stop_exec(char *msg)
{
	printf("%s\n", msg);
	exit(0);
}

void	list_dir(char *path)
{
	DIR		*dir;
	struct dirent *dirent;

	if ((dir = opendir(path)) == NULL)
			stop_exec(strerror(errno));
	while ((dirent = readdir(dir)) != NULL)
	{
		if ( (ft_strcmp(dirent->d_name, ".") != 0) && (ft_strcmp(dirent->d_name, "..") != 0)) //ignorer les fichier cacher
			printf("%s\n", dirent->d_name);
	}
	closedir(dir);
}

int		main(int ac, char **av)
{
	//parsing
	if (ac == 1)
		list_dir(".");
	else if (ac > 1)
		list_dir(av[1]);
	return (0);
}
