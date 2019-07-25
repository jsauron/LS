#include "../includes/ft_ls.h"

/*t_tab       init_ptr_fct_sort()
  {
  ftab[0] = &name_alpha; //
  ftab[1] = &time; // -t
  ftab[2] = &reverse_alpha; // -r
  ftab[3] = &size; // -S
  ftab[4] = &not_sorted; // -f
  }
  
  
  tab[1] = &get_info; // -l
  tab[2] = &show_hide; // -a
  tab[3] = &recursive; // -R
  tab[4] = &time; // -t
  ftab[5] = &reverse_alpha; // -r
  ftab[0] = &size; -S // 
      bjv ftab[0] = &not_sorted; // -f

  }
  */
t_element     *sort_elem_by(t_element *curr, int(*sort)(struct t_element *, struct t_element *))
{
  t_element *head;
  char    *tmp;

  head = curr;
  while (curr && curr->next)
  {
    if ((*sort)(curr, curr->next) != 0)
    {
      tmp = curr->name;

      curr->name = curr->next->name;
      curr->next->name = tmp;
      curr = head;
    }
    else
      curr = curr->next;
  }
  curr = head;
  return (curr);
}

int   name(t_element *curr, t_element *next)
{
  int i;

  i = 0;
  while (curr->name[i] - next->name[i] == 0) 
    i++;
  if (curr->name[i] - next->name[i] > 0)
    return (-1);
  return (0);
}
