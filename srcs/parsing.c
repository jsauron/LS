#include "../includes/ft_ls.h"

int   parse_flag(t_flag *flag, char *av)
{
  int i;
  char *sort;
  
  i = 1;
  sort = flag->sort;
  while (av[i] && ft_isprint(av[i]))
  {
    if (av[i] == 'r' && !ft_strchr(sort, 2))
      *flag->sort++ = 2; 
    else if (av[i] == 't' && !ft_strchr(sort, 1))
      *flag->sort++ = 1;  
    else if (av[i] == 'S' && !ft_strchr(sort, 3))
      *flag->sort++ = 3;  
    //else if (av[i] == 'f' && !ft_strchr(sort, 4))
      //*flag->sort++ = 4;
    else if  (av[i] == 'R')
		  flag->r = 1;
    else if (av[i] == 'l')
		flag->l = 1;
	else if (av[i] == 'a')
		flag->a = 1;
	i++;
  }
  *flag->sort = '\0';
  flag->sort = ft_strdup(sort);
  i = 0;
  while (flag->sort[i])
	printf("flag->sort = %d\n", flag->sort[i++]);
  return (1);
}

int		parse_file(t_flag *flag, char **av, int i)
{
	int j;

	j = 0;
	while (av[i])
			flag->file[j++] = ft_strdup(av[i++]);
	flag->file[j] = NULL;
	return (1);
}

int   parse(t_flag *flag, int ac, char **av)
{
  int i;

  i = 1;
  init_flag_struct(flag);
  *flag->file = ft_strdup(".");
  while (i < ac)
  {
		if (av[i][0] == '-' && av[i][1] && av[i][1] != '-')
      parse_flag(flag, av[i]);
	else if ((av[i][0] != '-')
      || (av[i][0] == '-' && av[i][1] && av[i][1] == '-'))
	{
		flag->sort = NULL;
		return (parse_file(flag, av, i));
	}
    i++;
  }
  return (0);
}
