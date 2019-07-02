/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 19:11:23 by jsauron           #+#    #+#             */
/*   Updated: 2019/07/02 11:26:03 by jsauron          ###   ########.fr       */
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

	dir = opendir(path);
	while ((dirent = readdir(dir)) != NULL)
		printf("%s\n", dirent->d_name);
	closedir(dir);
}

int		main(int ac, char **av)
{
	//parsing
	if (ac == 1)
		list_dir(".");
	return (0);
}
