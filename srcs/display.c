/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 13:57:08 by jsauron           #+#    #+#             */
/*   Updated: 2019/08/08 21:26:42 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		add_to_buff(t_flag *flag,  char *s)
{
	if ((int)ft_strlen(flag->buf) > 4000)
		ft_bzero(&flag->buf, 4096);
	ft_strcat(flag->buf, (const char *)s);
	return (0);
}


void	ft_void()
{
	int i = 0;
	i++;
}

int		add_to_lign(t_flag *flag, char *s, int i)
{
	if (i == flag->nb_col - 1)
	{
		add_to_buff(flag, flag->mini_buf);
		if (!flag->mini_buf)
			ft_void();
		flag->mini_buf = fill_wth_space(flag->mini_buf, flag->len_win);
		i = 0;
	}
	ft_strncpy(&flag->mini_buf[flag->tab[i]], (const char *)s, ft_strlen(s));
	return (i);
}

void  print_list(t_flag *flag, t_element *d)
{
	int i;

	i = 0;
	init_display(flag, d);
	d = d->next;
//	sort_column_list(flag, d);
	if (flag->l)
		printf("Total = %d\n", d->info->total);
	while (d != NULL)
	{
		if (flag->l)
			print_info(flag, d, d->info);
		else if (d->info->type && !flag->l)
		{
			//	add_to_buff(flag, "\033[36m\033[1m");
			i = add_to_lign(flag, d->name, i);
			//	add_to_buff(flag, "\033[0m");
		}
		else if (!d->info->type && !flag->l)
			i = add_to_lign(flag,  d->name, i);
		d = d->next;
		i++;
	}
	add_to_buff(flag, flag->mini_buf);
	add_to_buff(flag, "\n");
}
