#include "../includes/ft_ls.h"

int   init_flag(t_flag *flag)
{
    flag->sort = 0;
    //  flag->tab[7] = {'r','t','S','f','l','R','a'};
    return (1);
 }

int   parse_flag(t_flag *flag, char *av)
{
  int i;
  int j;

  i = 1;
  j = 0;
  while (av[i])
  {
    j = 0;
    while (&flag->tab[j])
    {
      if (ft_strcmp(&flag->tab[j], &av[i]) != 0)
      {
        flag->sort *= (j < 4) ? 10 + j : 0;
        flag->option *= (j >= 4) ? 10 + j : 0;
      }
      j++;
    }
    i++;
  }
  printf("sort = %d\n", flag->sort);
  printf("option = %d\n", flag->option);
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

  //if (i < j)
  //    //printf("ls: %s: No such file or directory", av[j]);
  return (1);
}
