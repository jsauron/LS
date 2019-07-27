#include "../includes/ft_ls.h"

int   parse_flag(t_flag *flag, char *av)
{
  int i;
  char *sort;

  i = 0;
  printf("av = %s\n", av);
  flag->sort = malloc(sizeof(char) * 10);
  while(i < 9)
  {
    flag->sort[i] = 'a';
    i++;
  }
  flag->sort[9] = '\0';
  printf("sort = %s\n", flag->sort);
  sort = flag->sort;
  i = 0;
  while (av[i++])
  {
    printf("av[%d] = %c\n", i, (av[i]));
    if (av[i] == 'r')
      *flag->sort++ = 2; // verifier les doublons 
    else if (av[i] == 't')
      *flag->sort++ = 3; // verifier les doublons 
    else if (av[i] == 'S')
      *flag->sort++ = 1; // verifier les doublons 
    else if (av[i] == 'f')
      *flag->sort++ = 4 ; // verifier les doublons 
    flag->r = (av[i] == 'R') ? 1 : 0;
    flag->l = (av[i] == 'l') ? 1 : 0;
    flag->a = (av[i] == 'a') ? 1 : 0;
  }
  *flag->sort = '\0';
  flag->sort = ft_strdup(sort);
  printf("sort = %d\n", ft_atoi(flag->sort));

  return (1);
}

int   parse(t_flag *flag, int ac, char **av)
{
  int i;

  (void)av;
  (void)ac;
  i = 1;
  flag->r = 0;
  flag->l = 0;
  flag->a = 0;
  flag->sort = NULL;
  //flag->ftab = malloc(sizeof(fcn) * 4);
  //init_ptr_sort(flag->ftab);
  flag->ftab[0] = &ascii;
  flag->ftab[1] = &time_modif; // -t
  flag->ftab[2] = &reverse_ascii; // -r
  flag->ftab[3] = &size; // -S
  while (av[i])
  {
    if (av[i][0] == '-')
      parse_flag(flag, av[i]);
    i++;
  }
  return (1);
}
