/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 19:40:24 by jsauron           #+#    #+#             */
/*   Updated: 2019/08/05 21:27:18 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/ft_ls.h"

int		init_flag_struct(t_flag *flag)
{
	ft_bzero(flag,  sizeof(t_flag));
	if (!(flag->file = malloc(sizeof(char *))))
		return (0);
	if (!(flag->buf = malloc(sizeof(char *) * 4096)))
		return (0);
	ft_memset(flag->buf, 0, 4096);
	*flag->file = NULL;
	return (1);
}
