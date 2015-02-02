/*
** allocation.c for  in /home/lastru_g/rendu/PSU_2014_malloc
**
** Made by lastrucci
** Login   <lastru_g@epitech.net>
**
** Started on  Thu Feb 13 13:43:05 2014 lastrucci
** Last update Sat Feb 15 13:12:32 2014 lastrucci
*/

#include <unistd.h>
#include "./malloc.h"

t_meta		*choise_to_creat_meta(size_t size, t_meta *tmp)
{
  t_meta	*new;
  void		*ptr_break;

  ptr_break = tmp->ptr_break;
  if (((void *)tmp + SIZE_T_M + tmp->size + SIZE_T_M + size) <= ptr_break)
    {
      new = (void *)tmp + SIZE_T_M + tmp->size;
      new->free = 0;
      new->size = size;
      new->next = NULL;
      new->prev = tmp;
      new->ptr_break = ptr_break;
      tmp->next = new;
      return (new);
    }
  return (creat_meta_by_alloc(size, tmp));
}

t_meta		*creat_meta_by_alloc(size_t size, t_meta *tmp)
{
  t_meta	*new;
  void		*last_break;
  void		*ptr_break;

  last_break = NULL;
  if ((ptr_break = call_sbrk(size, &last_break)) == NULL)
    return (NULL);
  if (tmp->ptr_break == last_break)
    new = tmp->ptr_break;
  else
    new = last_break;
  new->free = 0;
  new->size = size;
  new->next = NULL;
  new->prev = tmp;
  new->ptr_break = ptr_break;
  return (new);
}
