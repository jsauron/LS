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
		f->mode = ft_strdup(ft_strmode(statbuf.st_mode));
		f->nb_lien =  statbuf.st_nlink;
		f->user = ft_strdup((getpwuid(statbuf.st_uid))->pw_name);
		f->gr_user = (getgrgid(statbuf.st_gid))->gr_name;
		f->size = statbuf.st_size;
		f->time = ctime(&statbuf.st_mtime);
		f->type = (S_ISDIR(statbuf.st_mode)) ? 1 : 0;
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
		print_info(statbuf);
}

void  print_list_1(t_element *d)
{
  printf("\n");
  d= d->next;
  while (d != NULL)
  {
    printf("---%s\n", d->name);
    //printf("---%zu\n", d->info->size);
    //printf("---%s\n", d->info->mode);
    d = d->next;
  }
}

char  *path_dir(char *path)
{
  char  *head;

  head = path;
  while (*path)
    path++;
  while (*path != '/')
  {
   *path = '\0';
   path--;
  }
  *path = '\0';
  return (ft_strdup(head)); 
}

void  print_list_2(t_element *d)
{
  d = d->next;
  while (d != NULL)
  {
    if (d->info->type)
          printf("\033[36m\033[1m%s\t \033[0m", d->name);
    else
      printf("%s\t", d->name);
    if (d->next)
      d->stair < d->next->stair ? printf("\n\n%s\n", path_dir(d->next->path)) : 0;
  d = d->next;
  }
  printf("\n");
}

t_element		*listing_dir_all(char *path, t_element *curr)
{
		DIR				*dir;
		struct dirent	*dirent;
		struct stat statbuf;

		dir = NULL;
		dirent = NULL;

		if (lstat(path, &statbuf) == -1)
			stop_exec(strerror(errno));
		if (S_ISDIR(statbuf.st_mode)/* && ft_strcmp(path, dirent->d_name) == 0*/)
    {
      if ((dir = opendir(path)) == NULL)
				stop_exec(strerror(errno));

		  curr = read_all(curr, path, dirent, dir, statbuf);
	  	closedir(dir);

		check_dir(curr->head, curr);
    }
  else
    printf("%s\n", path);
		return (curr->head);
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
			print_list_2(listing_dir_all(av[2], init_list(av[2])));
	}
	else if (ac > 1)
		parse(av[1]);

	return (0);
}
