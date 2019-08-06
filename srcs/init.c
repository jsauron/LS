/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 19:40:24 by jsauron           #+#    #+#             */
/*   Updated: 2019/08/06 18:00:12 by jsauron          ###   ########.fr       */
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
