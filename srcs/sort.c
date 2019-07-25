#include "../includes/ft_ls.h"

/*t_tab       init_tab_ptr_fct()
  {
  ftab[0] = &name;
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
