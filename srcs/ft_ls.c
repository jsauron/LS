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

/*int		list_dir(struct dirent *dirent, DIR *dir, struct stat statbuf, char *path)
{
  char *new_path;

  new_path = NULL;
		while ((dirent = readdir(dir)) != NULL)
			if ( (ft_strcmp(dirent->d_name, ".") != 0)
          && (ft_strcmp(dirent->d_name, "..") != 0) && *dirent->d_name != '.')
      {
        new_path = ft_addstr(path, ft_addstr("/", dirent->d_name));
        lstat(new_path, &statbuf);
        (S_ISDIR(statbuf.st_mode)) ? printf("\033[36m\033[1m%s\t \033[0m", dirent->d_name) : printf("%s\t", dirent->d_name);

      }
    return (1);
}
*/
t_element		*listing_dir_all(char *path, t_element *curr, int r)
{
		DIR				*dir;
		struct dirent	*dirent;
		struct stat statbuf;

		dir = NULL;
		dirent = NULL;

		(lstat(path, &statbuf) == -1) ? stop_exec(strerror(errno)) : 0;
		if (S_ISDIR(statbuf.st_mode)/* && ft_strcmp(path, dirent->d_name) == 0*/)
    {
      (dir = opendir(path)) ? 0 : stop_exec(strerror(errno));
		  curr = read_all(curr, path, dirent, dir, statbuf);
	  	closedir(dir); 
		  r ? check_dir(curr->head, curr) : 0;
    }
  else
    printf("%s\n", path);
  sort_elem_by(curr->head->next, name);
		return (curr->head);
}


int		main(int ac, char **av)
{
	//char	arg[5]  = {'l', 'R', 'a', 'r', 't'};
	//int (*flag[2])(char*, struct dirent *dirent, DIR *, struct stat*) = {list_dir, create_list};
	if (ac == 1)
		print_list_2(listing_dir_all(".", init_list("."), 0));
	else if (ft_strcmp(av[1], "-R") == 0)
	{
	if (ac < 3)
			print_list_2(listing_dir_all(".", init_list("."), 2));
		else if (ac == 3)
			print_list_2(listing_dir_all(av[2], init_list(av[2]), 1));
	}
	else if (ac > 1)
		print_list_2(listing_dir_all(av[1], init_list(av[2]), 0));

	return (0);
}
