#include "../includes/ft_ls.h"

int   parse_flag(t_flag *flag, char *av)
{
  int i;
  int j;
  char *option;
  char *sort;

  i = 1;
  j = 0;
  option = flag->option;
  sort = flag->sort;
  while (av[i])
  {
    if (av[i] == 'r' || av[i] == 't' || av[i] == 'S' || av[i] == 'f')
        *flag->sort++ = av[i]; // verifier les doublons 
    if (av[i] == 'l' || av[i] == 'a')
        *flag->option++ = av[i];
    flag->r = (av[i] == 'R') ? 1 : 0;
  }
  flag->option = ft_strdup(option);
  flag->sort = ft_strdup(sort);
  printf("sort = %s\n", flag->sort);
  printf("option = %s\n", flag->option);
  return (1);
}

int   parse(t_flag *flag, int ac, char **av)
{
  int i;

  (void)ac;
  i = 0;
  while (av[i])
  {
    if (av[i][0] == '-')
      parse_flag(flag, av[i]);
    i++;
  }
  return (1);
}
