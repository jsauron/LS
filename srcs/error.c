/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 16:38:19 by jsauron           #+#    #+#             */
/*   Updated: 2019/08/07 15:53:51 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		flag_error(char c)
{
	printf("ls: illegal option -- %c\n", c);
	printf("usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]\n");
	return (0);
}


void  stop_exec(char *msg)
{
	printf("%s\n", msg);
	exit(0);
}
