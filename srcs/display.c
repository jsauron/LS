/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 13:57:08 by jsauron           #+#    #+#             */
/*   Updated: 2019/08/07 16:07:44 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		add_to_buff(t_flag *flag,  char *s)
{
//	mini_buf = ft_memset(flag->mini_buf, ' ', (size_t)flag->len_s);
	//ft_strcpy_on(mini_buf, s);
	//ft_strcat(flag->mini_buf, (const char *)s);
	ft_strcat(flag->buf, (const char *)s);
	if (!s)
		free(s);
	return (0);
}
/*int		add_to_lign(t_flag *flag, char *s)
{


}
*/
void  print_list(t_flag *flag, t_element *d)
{
	init_display(flag, d);
	d = d->next;
	if (flag->l)
		printf("Total = %d\n", d->info->total);
	while (d != NULL)
	{
		if (flag->l)
			print_info(flag, d, d->info);
		else if (d->info->type && !flag->l)
		{
			add_to_buff(flag, "\033[36m\033[1m");
			add_to_buff(flag, d->name);
			add_to_buff(flag, "\t \033[0m");
		}
		else if (!d->info->type && !flag->l)
		{
			add_to_buff(flag,  d->name);
				add_to_buff(flag, "\t");
		}
		d = d->next;
	}
	add_to_buff(flag, "\n");
 //free les truc de display
}
