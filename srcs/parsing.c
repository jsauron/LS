#include "../includes/ft_ls.h"

int   parse_flag(t_flag *flag, char *av)
{
	int i;
	
	i = 1;
	if (!(flag->sort = malloc(sizeof(fcn))))
		return (0);
	*flag->sort = NULL	;
	while (av[i] && ft_isprint(av[i]))
	{
		if (av[i] == 'r')
			*flag->sort = &reverse_ascii; 
		else if (av[i] == 't')
			*flag->sort =  &time_modif;
		else if (av[i] == 'S')
			*flag->sort = &size;
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
	while (i < ac)
	{
		if (av[i][0] == '-' && av[i][1] && av[i][1] != '-')
		{
			if (!parse_flag(flag, av[i]))
			return (0);
		}
		else if ((av[i][0] != '-')
				|| (av[i][0] == '-' && av[i][1] && av[i][1] == '-'))
			return (parse_file(flag, av, i));
		i++;
	}
	*flag->file = ft_strdup(".");
	return (1);
}
