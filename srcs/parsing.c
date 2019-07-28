#include "../includes/ft_ls.h"

int   parse_flag(t_flag *flag, char *av)
{
  int i;
  char *sort;

  i = 1;
  sort = flag->sort;
  while (av[i] && ft_isprint(av[i]))
  {
    if (av[i] == 'r')
      *flag->sort++ = 2; // verifier les doublons 
    else if (av[i] == 't')
      *flag->sort++ = 1; // verifier les doublons 
    else if (av[i] == 'S')
      *flag->sort++ = 3; // verifier les doublons 
    else if (av[i] == 'f')
      *flag->sort++ = 4 ; // verifier les doublons 
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
  return (1);
}

int		parse_file(t_flag *flag, char **av, int i)
{
	int j;

	j = 0;
	while (av[i])
		if (av[i][0] != '-')
			flag->file[j++] = ft_strdup(av[i++]);
	flag->file[j] = NULL;
	return (1);
}

int   parse(t_flag *flag, int ac, char **av)
{
  int i;

  i = 1;
  //init_ptr_sort(flag->ftab);
  flag->r = 0;
  flag->l = 0;
  flag->a = 0;
  flag->file = malloc(sizeof(char *) * 1);
  flag->sort = (ac == 1) ? ft_memalloc(1) : malloc(sizeof(char) * 1);
  
  flag->ftab[0] = &ascii;
  flag->ftab[1] = &time_modif; // -t
  flag->ftab[2] = &reverse_ascii; // -r
  flag->ftab[3] = &size; // -S
  *flag->file = ft_strdup(".");
  while (i < ac)
  {
    if (av[i][0] == '-')
      parse_flag(flag, av[i]);
	else
	{
		flag->sort = NULL;
		return (parse_file(flag, av, i));
	}
    i++;
  }
  return (0);
}
