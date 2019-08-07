/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 19:40:24 by jsauron           #+#    #+#             */
/*   Updated: 2019/08/07 16:10:28 by jsauron          ###   ########.fr       */
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


int		init_flag_struct(t_flag *flag)
{
	ft_bzero(flag,  sizeof(t_flag));
	if (!(flag->file = malloc(sizeof(char *))))
		return (0);
	*flag->file = NULL;
	return (1);
}

int		init_display_tab(t_flag *flag)
{
	int i;

	i = 0;
	if (!(flag->tab = malloc(sizeof(int) * flag->nb_by_lign - 1)))
		return (-1);
	while (i < flag->nb_by_lign - 1)
	{
		flag->tab[i] = i * flag->len_max;
		i++;
	}
	i = 0;
	while (i < flag->nb_by_lign - 1)
	{
		printf("tab[%d] = %d\n", i, flag->tab[i]);
		i++;
	}

	return (0);
}

int		init_display(t_flag *flag, t_element *d)
{
	struct  winsize ws;

	ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
	flag->len_max = get_len_max(d) + 1;
	flag->len_win = ws.ws_col + 1;
	flag->nb_by_lign = flag->len_win / flag->len_max;
	if (!(flag->mini_buf = malloc(sizeof(char)* flag->len_win)))
		stop_exec("malloc minibuf failed\n");
	init_display_tab(flag);
	return (0);
}
