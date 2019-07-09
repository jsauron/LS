/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 17:03:59 by jsauron           #+#    #+#             */
/*   Updated: 2019/07/09 17:58:22 by jsauron          ###   ########.fr       */
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

int		print_list(t_dir *d)
{
	int		c;

	c = 0;
	while (d != NULL)
	{
		//write(1, "\033[36m", 5);
		//if (c % 5 == 0)
		//	printf("\n");
		printf(" name = %s ", d->name);
		printf("size = %zu ", d->info.size);
		printf("mode = %s ", d->info.mode);
		d = d->next;
		printf("c = %d\n", c);
		c++;
	}
	return (1);
}

int		create_list(char *path, struct dirent *dirent, DIR *dir,  struct stat statbuf)
{
	t_dir	*curr;
	t_dir	*head;
	struct stat		stat_b;

	curr = NULL;
	curr = malloc(sizeof(t_dir));
	head = curr;
	if (S_ISDIR(statbuf.st_mode))
	{
		while ((dirent = readdir(dir)) != NULL)
		{
			if ((ft_strcmp(dirent->d_name, ".") != 0) && (ft_strcmp(dirent->d_name, "..") != 0))
			{
				curr->type = "Directory";
				curr->name = dirent->d_name;
				curr->path = ft_addstr(path, ft_addstr("/", dirent->d_name));
				lstat(curr->path ,&stat_b);
				get_info_in_list(&curr->info, path, dirent, stat_b);
				curr->next = malloc(sizeof(t_dir));
				curr = curr->next;
			}
		}
		curr->next = NULL;
		print_list(head);
	}
	return (1);
}
