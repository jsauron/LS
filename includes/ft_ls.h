/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 18:42:46 by jsauron           #+#    #+#             */
/*   Updated: 2019/07/23 13:23:42 by jsauron          ###   ########.fr       */
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
	char			*user;
	char			*gr_user;
	size_t			size;
	char			*time;
}					t_info;

typedef struct		t_file
{
	char			*name;
	char			*path;
	t_info			info;
	struct t_file			*next;
	struct t_file			*before;
}					t_file;

typedef struct		t_dir
{
	int				index;
	int				hide;
	char			*name;
	char			*path;
	char			*type;
	t_file			*file;
	t_info			info;
	struct t_dir			*next;
	struct t_dir			*before;

}					t_dir;

//ADD TO LIBFFT FUNCTION
char	*ft_strmode(mode_t mode);
int		print_list(t_dir *d);
int		add_dir(t_dir	*curr, struct stat statb, struct dirent *dirent, char *path);
int		add_file();
int		create_list(char *path, struct dirent *dirent, DIR *dir, t_dir *curr);
int		get_info_in_list(t_info *f, struct stat statbuf);
int		fonction_r(char *path, t_dir *curr);
#endif
