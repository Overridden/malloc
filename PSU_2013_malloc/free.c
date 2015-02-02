/*
** my_free.c for  in /home/lastru_g/rendu/test
**
** Made by lastrucci
** Login   <lastru_g@epitech.net>
**
** Started on  Thu Feb 13 16:16:16 2014 lastrucci
** Last update Sat Feb 15 15:31:42 2014 lastrucci
*/

#include <unistd.h>
#include "./malloc.h"

t_meta		*check_whith_2_meta(t_meta *first_tmp, t_meta *second_tmp, char pos)
{
  if ((void *)first_tmp + SIZE_T_M + first_tmp->size == (void *)second_tmp)
    {
      first_tmp->size += SIZE_T_M + second_tmp->size;
      first_tmp->next = second_tmp->next;
      first_tmp->ptr_break = second_tmp->ptr_break;
      if (second_tmp->next)
	second_tmp->next->prev = first_tmp;
      return (first_tmp);
    }
  if (pos == 1)
    return (first_tmp);
  return (second_tmp);
}

void		free(void *ptr)
{
  t_meta	*tmp;

  tmp = g__ptr__;
  if (!tmp)
    return ;
  while (tmp != ptr - SIZE_T_M && tmp != NULL)
    tmp = tmp->next;
  if (!tmp)
    return ;
  tmp->free = 1;
  if (tmp->next && tmp->next->free == 1)
    tmp = check_whith_2_meta(tmp, tmp->next, 1);
  if (tmp->prev && tmp->prev->free == 1)
    tmp = check_whith_2_meta(tmp->prev, tmp, 0);
  if (tmp->prev && tmp->next == NULL &&
      ((void *)tmp + tmp->prev->size + SIZE_T_M) == tmp)
    {
      tmp->prev->ptr_break = tmp->ptr_break;
      tmp->prev->next = NULL;
    }
  if (tmp->prev == NULL && tmp->next == NULL)
    {
      brk((void *)g__ptr__);
      g__ptr__ = NULL;
    }
}
