/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 19:11:23 by jsauron           #+#    #+#             */
/*   Updated: 2019/07/24 13:23:33 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	stop_exec(char *msg)
{
  printf("%s\n", msg);
  exit(0);
}

int		get_info_in_list(t_info *f, struct stat statbuf)
{
  //		printf("file = %s, %s\n", dirent->d_name, ft_strmode(statbuf.st_mode));
  if (S_ISREG(statbuf.st_mode)/* && ft_strcmp(path, dirent->d_name) == 0*/)
  {
    //		printf("Type: Fichier\n");
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
  (void)path;
  (void)dirent;
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
  (void)path;
  (void)dirent;
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
  dirent = NULL;
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

int		open_dir(char *path, t_dir *curr/*, *((int)fnc(void)*/)
    {
    DIR				*dir;
    struct dirent	*dirent;
    struct stat		statbuf;

    dir = NULL;
    dirent = NULL;
    if (lstat(path, &statbuf) == -1)
    stop_exec(strerror(errno));
    if (S_ISDIR(statbuf.st_mode)/* && ft_strcmp(path, dirent->d_name) == 0*/)
    {
    if ((dir = opendir(path)) == NULL)
    stop_exec(strerror(errno));
    }
    // utiliser open_dir avec un pointeur sur fonction correspondant au flag
    if (!(curr->file = malloc(sizeof(t_file))))
      stop_exec("malloc curr->file in open_dir");
    curr = create_list(path, dirent, dir, curr);
  printf("ptr_opendir = %p\n", curr);
    //list_dir
    closedir(dir);
    return (1);
    }


int   fonction_r(t_dir *curr, struct stat statbuf, struct dirent *dirent, DIR *dir, char *path)
{	

  t_dir   *new;


  if ((!(new = malloc(sizeof(t_dir))))/* || (!(new->file = malloc(sizeof(t_file))))*/)
    stop_exec("malloc curr next in fonction_r failed");
  curr->next  = new;
  new->next = NULL;
  printf("new->next = %p\n", curr->next);
  curr = curr->next;
  if (lstat(path, &statbuf) == -1)
    stop_exec(strerror(errno));
  if (S_ISDIR(statbuf.st_mode)/* && ft_strcmp(path, dirent->d_name) == 0*/)
  {
    if ((dir = opendir(path)) == NULL)
      stop_exec(strerror(errno));
  }
  write(1, C_CYAN, 5);
  write(1, C_BOLD, 5);
  printf("%s\n", path);
  write(1, C_NONE, 5);
  printf("curr avant creatlist = %p\n", curr);
  create_list(path, dirent, dir, curr);
  printf("lalala\n");
  closedir(dir);

//else if (S_ISREG(statbuf.st_mode))
//	printf("%s\n", path);
return (1);
}


int		main(int ac, char **av)
{
  t_dir	*curr;
  t_dir	*head;

  if (!(curr = malloc(sizeof(t_dir))))
    stop_exec("malloc curr in main failed");
  curr->next = NULL;
  head = curr;
  //char	arg[5]  = {'l', 'R', 'a', 'r', 't'};
  //int (*flag[2])(char*, struct dirent *dirent, DIR *, struct stat*) = {list_dir, create_list};
  if (ac == 1)
    parse(".");
  else if (ft_strcmp(av[1], "-R") == 0)
  {
    if (ac < 3) 
      open_dir(".", curr);
    else if (ac == 3)
      open_dir(av[2], curr);
 // printf("pt3r = %p\n", curr);
  print_list(head);
  }
  else if (ac > 1)
    parse(av[1]);

  return (0);
}
