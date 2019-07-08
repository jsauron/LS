/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 17:03:59 by jsauron           #+#    #+#             */
/*   Updated: 2019/07/08 19:03:39 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char	*ft_addstr(char *s1, char *s2)
{
	char	*res;
	int i;
	int j;

	j = 0;
	i = 0;
	res = NULL;

	while ( s1 && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	printf("res = %s\n", res);
	while ( s2 && s2[j])
		res[i++] = s2[j++];
	printf("res2 = %s\n", res);
	res[i] = '\0';
	return (res);
}

int		print_list(t_dir *d)
{
	int		c;

	c = 0;
		printf("print_list\n");
	if (d == NULL)
		printf("NULL\n");
	if (d->next == NULL)
		printf(" next NULL\n");
	while (d && d->next != NULL)
	{
		if (c % 5 == 0)
			printf("\n");
		printf("%s\t", d->name);
		printf("%zu\n", d->info.size);
		printf("%s\n", d->info.mode);
		write(1, "\x1b[36m", 5);
		d = d->next;
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
			curr->name = dirent->d_name;
			printf("%s\n", path );
			printf("%s\n", ft_addstr("kakaka", "jskjs"));
		//	lstat(ft_strcat(path, dirent->d_name), &stat_b);
			get_info_in_list(&curr->info, path, dirent, stat_b);
			curr->next = malloc(sizeof(t_dir));
			curr = curr->next;
		}
		curr->next = NULL;
	}
	print_list(head);
	return (1);
}
