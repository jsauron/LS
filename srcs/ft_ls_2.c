/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 17:03:59 by jsauron           #+#    #+#             */
/*   Updated: 2019/07/24 13:39:27 by jsauron          ###   ########.fr       */
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
  printf("ptrfinal = %p\n", d);
  while (d != NULL)
  {
    //write(1, "\033[36m", 5);
    //if (c % 5 == 0)
    printf(" path = %s\n ", d->path);
    //printf(" name = %s\n ", d->name);
    d = d->next;
    printf("c = %d\n", c);
    c++;
  }
  return (1);
}


int		add_dir(t_dir *curr, struct stat statb, struct dirent *dirent, char *path, DIR *dir )
{
  int static i;

  printf("ptradddir = %p\n", curr);
  printf("%s\t creer\n", dirent->d_name);
  curr->type = "Directory";
  curr->name = dirent->d_name;
  printf(" curr name ###### %s\n", curr->name);
  curr->index = i++;
  curr->path = path;
  get_info_in_list(&curr->info, statb);
  fonction_r(curr, statb, dirent, dir, path);
  printf("%d\n", i);
  return (1);
}

/*int		add_file(t_dir *curr, struct stat statb, char *name, char *path)
  {
  t_file	*before;

  curr->file = malloc(sizeof(t_file));
  before = curr->file;
  printf("la\n");
  curr->file->name = name;
  curr->file->path = path;
  get_info_in_list(&curr->file->info, statb);
  curr->file->next = malloc(sizeof(t_file));
  curr->file = curr->file->next;
  curr->file->before = before;
  return (1);
  }
  */
t_dir		*create_list(char *path, struct dirent *dirent, DIR *dir, t_dir *curr)
{
  struct stat		stat_b;
  char	*new_path;
  t_dir   *new;
  new_path = NULL;
  while ((dirent = readdir(dir)) != NULL)
  {
    if ((ft_strcmp(dirent->d_name, ".") != 0) && (ft_strcmp(dirent->d_name, "..") != 0))
    {
      new_path = ft_addstr(path, ft_addstr("/", dirent->d_name));
      lstat(new_path ,&stat_b);
      if (S_ISDIR(stat_b.st_mode))
      {
        add_dir(curr, stat_b,  dirent, new_path, dir);
      /*			else if (S_ISREG(stat_b.st_mode))
              {
              printf("%s\t", dirent->d_name );
              add_file(curr, stat_b, dirent->d_name, new_path);
              }
              free(new_path);
              */
      printf("---------------name curr %s\n", curr->name);
		if ((!(new = malloc(sizeof(t_dir)))) /*|| (!(new->file = malloc(sizeof(t_file))))*/)
        stop_exec("malloc curr next in fonction_r failed");
      curr->next  = new;
      new->next = NULL;
      printf("new in last = %p\n", new);
      printf("curr in last = %p\n", curr);
      curr = curr->next;
      printf("curr in last2 = %p\n", curr);
    }
    }
  }
  //curr->file->next = NULL;
  printf("jump\n");
  curr->next = NULL;
  return (curr);
}
