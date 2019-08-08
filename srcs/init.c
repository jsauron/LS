/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 19:40:24 by jsauron           #+#    #+#             */
/*   Updated: 2019/08/08 22:22:54 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/ft_ls.h"
t_element	*init_list(char *path)
{
	t_element	*curr;

	(curr = malloc(sizeof(t_element))) == NULL ? stop_exec("malloc curr failed") : 0;
	(curr->info = malloc(sizeof(t_info))) == NULL ? stop_exec("malloc info failed") : 0;
	ft_bzero(curr->info, sizeof(t_info));
	curr->head = curr;
	curr->name = ft_strdup(path);
	curr->path = ft_strdup(path);
	curr->next = NULL;
	return (curr);
}

char		*fill_wth_space(char *str, int len)
{
	int i;

	i = 0;
	if (!str)
		return (NULL);
	while (i < len && str && str[i])
		str[i++] = ' ';
	return (str);
}

int		init_flag_struct(t_flag *flag)
{
	struct  winsize ws;
	ft_bzero(flag,  sizeof(t_flag));
	//if (!(flag->file = malloc(sizeof(char *))))
	//	return (-1);
	*flag->file = NULL;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
	flag->len_win = ws.ws_col;
	return (0);
}

int		init_display_tab(t_flag *flag)
{
	int i;

	i = 0;
	if (!(flag->tab = malloc(sizeof(int) * flag->nb_col - 1)))
		return (-1);
	while (i < flag->nb_col - 1)
	{
		flag->tab[i] = i * flag->len_max;
		i++;
	}
	return (0);
}

int		init_display(t_flag *flag, t_element *d)
{
	int		i;

	i = 0;
	flag->len_max = get_len_max(d) + 1;
	if (flag->len_max > flag->len_win)
		flag->nb_col = 1;
	else
		flag->nb_col = flag->len_win / flag->len_max;
	if (!(flag->mini_buf = malloc(sizeof(char)* flag->len_win)))
		stop_exec("malloc minibuf failed\n");
	flag->len_list = len_list(d);
	flag->nb_lign = flag->len_list / flag->nb_col;
	flag->nb_col =  (flag->len_list < flag->nb_col) ? flag->len_list : flag->nb_col;
	init_display_tab(flag);
	flag->mini_buf = fill_wth_space(flag->mini_buf,flag->len_win);
	return (0);
}
