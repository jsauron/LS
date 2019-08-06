#include "../includes/ft_ls.h"

void  stop_exec(char *msg)
{
	printf("%s\n", msg);
	exit(0);
}

int	add_to_buff(char *buf, char *s)
{

	ft_strcat(buf, (const char *)s);
	if (!s)
		free(s);
	return (0);
}

void  free_list(t_element *d)
{
	t_element *tmp;

	tmp = NULL;
	while (d)
	{
		tmp = d->next;
/*		free(d->path);
		free(d->name);
		free(d->head);
		free(d->info->mode);
		free(d->info->str_time);
		free(d->info->user);
		free(d->info->gr_user);
		free(d->info);
*/		free(d);
		d = tmp;
	}
	free(d);
}

char  *path_dir(char *path)
{
	char  *head;

	head = path;
	while (*path)
		path++;
	while (*path != '/')
	{
		*path = '\0';
		path--;
	}
	*path = '\0';
	return (ft_strdup(head));
}
/*
char	*make_str(char *s1, char *s2, char *s3, char *s4)
{
	char *str;

	str = ft_strjoinfree(ft_strjoin(s1, s2), ft_strjoin(s3, s4), 3);
	return (str);
}*/
/*
int		get_len_max(t_element *d)
{
	int len_max;

	len_max = 0;
	while (d->next != NULL)
	{
		if (ft_strlen(d->name) > len_max)
			len_max = ft_strlen(d->name);
		d = d->next;
	}
	return (len_max);
}
*/
/*int		column(t_flag *flag, t_element *d)
{
	int len_max;
	int len_s;;
	
	len = get_len_max;
	len_s = get_sizewindow;

}
*/
void  print_list(t_flag *flag, t_element *d)
{
//	column(flag, d);
	d = d->next;
	if (flag->l)
		printf("Total = %d\n", d->info->total);
	while (d != NULL)
	{
		if (flag->l)
			print_info(flag, d, d->info);
		else if (d->info->type && !flag->l)
		{
			add_to_buff(flag->buf, "\033[36m\033[1m");
			add_to_buff(flag->buf, d->name);
			add_to_buff(flag->buf, "\t \033[0m");
		}
		else if (!d->info->type && !flag->l)
		{
			add_to_buff(flag->buf,  d->name);
			add_to_buff(flag->buf, "\t");
		}
		d = d->next;
	}
	add_to_buff(flag->buf, "\n");
}

char  *ft_addstr(char *s1, char *s2)
{
	char  *res;
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
	while (s2 && s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
}
