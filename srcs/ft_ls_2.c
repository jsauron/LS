/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 17:03:59 by jsauron           #+#    #+#             */
/*   Updated: 2019/07/22 18:27:38 by jsauron          ###   ########.fr       */
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
	while (d->name != NULL)
	{
		//write(1, "\033[36m", 5);
		//if (c % 5 == 0)
		//	printf("\n");
		//	printf(" name = %s ", d->name);
		//		printf("size = %zu ", d->info.size);
		//		printf("mode = %s ", d->info.mode);
		d = d->next;
		//printf("d->name = %s\n", d->name);
		//printf("c = %d\n", c);
		//c++;
	}
	printf("la\n");
	return (1);
}


int		add_dir(t_dir *curr, struct stat statb,  char *name, char *path)
{
	int static i;

	printf(" dir %s\t", name);
	curr->type = "Directory";
	curr->name = name;
	curr->index = i++;
	curr->path = path;
	get_info_in_list(&curr->info, statb);
	curr->next = malloc(sizeof(t_dir));
	curr = curr->next;
	printf("%d\n", i);
	return (1);
}

int		add_file(t_file *file, struct stat statb, char *name, char *path)
{

	printf("la\n");
	file->name = name;
	file->path = path;
	get_info_in_list(&file->info, statb);
	return (1);
}

int		create_list(char *path, struct dirent *dirent, DIR *dir, t_dir *curr)
{
	t_dir	*head;
	struct stat		stat_b;
	char	*new_path;
	int	i;

	i = 0;
	new_path = NULL;
	head = curr;
	while ((dirent = readdir(dir)) != NULL)
	{
		if ((ft_strcmp(dirent->d_name, ".") != 0) && (ft_strcmp(dirent->d_name, "..") != 0))
		{
			//curr->next = malloc(sizeof(t_dir));
			//curr = curr->next;
			//	curr->name = dirent->d_name;
			//		printf("%s\t", dirent->d_name);
			new_path = ft_addstr(path, ft_addstr("/", dirent->d_name));
			//			if (S_ISDIR(statbuf.st_mode))
			//add_dir(curr, dirent->d_name, ft_addstr(path, ft_addstr("/", dirent->d_name)));
			//		printf("curr path = %s\n", curr->path);
			lstat(new_path ,&stat_b);
			if (S_ISDIR(stat_b.st_mode))
			{
				add_dir(curr, stat_b,  dirent->d_name, new_path);
				fonction_r(curr->path, curr);
			}
			if (S_ISREG(stat_b.st_mode))
			{
				printf("%s\t", dirent->d_name );
				add_file(curr->file[i], stat_b, dirent->d_name, new_path);
			}
			//get_info_in_list(&curr->info, path, dirent, stat_b);
			//				curr->next = malloc(sizeof(t_dir));
			//				curr = curr->next;
			//			printf("lala\n");
			//		curr  = malloc(sizeof(t_dir));
		i++;
		}
	}
	printf("\n");
	curr = NULL;
	return (1);
}
