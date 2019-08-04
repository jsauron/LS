/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 18:42:46 by jsauron           #+#    #+#             */
/*   Updated: 2019/07/29 18:17:42 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include "../libft/libft.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/xattr.h>
#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <string.h>
#include <grp.h>

/*
 * ** Color text
 * */

# define C_NONE         "\033[0m"
# define C_BOLD	       "\033[1m"
# define C_BLACK        "\033[30m"
# define C_RED          "\033[31m"
# define C_GREEN        "\033[32m"
# define C_BROWN        "\033[33m"
# define C_BLUE         "\033[34m"
# define C_MAGENTA      "\033[35m"
# define C_CYAN         "\033[36m"
# define C_GRAY         "\033[37m"


typedef struct		t_info
{
	char			*mode;
	int				nb_lien;
	int				type;
	char			*user;
	char			*gr_user;
	size_t			size;
	long			time;
	char			*str_time;
	int				state;
	int				stair;
	int				hide;
  int       total;
}					t_info;

typedef struct		t_element
{
	char			*name;
	char			*path;
	t_info			*info;
	struct t_element			*head;
	struct t_element			*next;
}					t_element;

typedef int (*fcn)(struct t_element *,struct t_element *);

typedef struct    t_flag
{
  char    **file;
  fcn     *sort;
  int       r;
  int       a;
  int       l;
}               t_flag;

int		flag_error(char c);
//ft_ls.c
int   get_info(t_info *f, struct stat statbuf);
int   list_dir(struct dirent *dirent, DIR *dir, struct stat stab, char *path);
int  parse(t_flag *flag, int ac, char **av);
t_element   *listing_dir_all(char *path, t_element *curr, t_flag *flag);
int   main(int ac, char **av);

//ft_ls_2.c
t_element   *init_list(char *path);
t_element     *read_all(t_flag *flag, t_element *curr, char *path,  DIR *dir, struct stat statbuf);
int     check_dir(t_element *head, t_element *curr, t_flag *flag);
t_element *add_node(t_element *curr, char *path, char *name, struct stat statb, int i);
//utils.c
void  stop_exec(char *msg);
char  *path_dir(char *path);
void  print_list(t_flag *flag, t_element *d);
int  print_info(t_element *d, t_info *f);
char  *ft_addstr(char *s1, char *s2);

//sort.c
int   stair(t_element *curr, t_element *next);
int           sort_list(t_flag *flag, t_element *curr);
t_element     *sort_elem_by(t_element *curr, int(*sort)(t_element *, t_element *));
t_element     *sort_name_by(t_element *curr, int(*sort)(t_element *, t_element *));
int   ascii(t_element *curr, t_element *next);
int   reverse_ascii(t_element *curr, t_element *next);
int   size(t_element *curr, t_element *next);
int   ascii_path(t_element *curr, t_element *next);
int   time_modif(t_element *curr, t_element *next);
int   init_ptr_sort(fcn *ftab);
int		init_flag_struct(t_flag *flag);
//parsing.c

//ADD TO LIBFFT FUNCTION
char	*ft_strmode(mode_t mode);

#endif
