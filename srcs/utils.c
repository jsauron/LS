#include "../includes/ft_ls.h"

void  stop_exec(char *msg)
{
  printf("%s\n", msg);
  exit(0);
}

void  free_list(t_element *d)
{
  t_element *tmp;

  tmp = NULL;
  while (d)
  {
    tmp = d->next;
    free(d);
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

void  print_list(t_flag *flag, t_element *d)
{
  d = d->next;
  //if (flag->l)
    //printf("Total = %d\n", d->info->total);
  while (d != NULL)
  {
  	if (flag->l)
	  	print_info(d, d->info);
    else if (d->info->type)
      printf("\033[36m\033[1m%s\t \033[0m", d->name);
    else if (!d->info->type) 
      printf("%s\t", d->name);
    if (d->next && !flag->l)
    {
      if (d->info->stair < d->next->info->stair)
        printf("\n\n%s:\n", path_dir(d->next->path));
    }
    d = d->next;
  }
  printf("\n");
  free_list(d);
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
  while ( s2 && s2[j])
    res[i++] = s2[j++];
  res[i] = '\0';
  return (res);
}
