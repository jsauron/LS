#include "../includes/ft_ls.h"

int	len_list(t_element *d)
{
	int len;

	len = 0;
	while (d != NULL)
	{
		len++;
		d = d->next;
	}
	return (len);
}

void  free_list(t_element *d)
{

	while (d)
	{
		free(d->path);
		free(d->name);
		free(d->head);
		free(d->info->mode);
		free(d->info->str_time);
		free(d->info->user);
		free(d->info->gr_user);
		free(d->info);
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

int		get_len_max(t_element *d)
{
	int len_max;

	len_max = 0;
	while (d->next != NULL)
	{
		if ((int)ft_strlen(d->name) > len_max)
		len_max = ft_strlen(d->name);
		d = d->next;
	}
	return (len_max);
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
	while (s1 && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
}
