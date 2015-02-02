/*
** malloc.c for  in /home/lastru_g/rendu/retest
**
** Made by lastrucci
** Login   <lastru_g@epitech.net>
**
** Started on  Sat Feb 15 10:15:01 2014 lastrucci
** Last update Fri Feb 21 10:16:21 2014 Alexandre NGUYEN
*/

#include <unistd.h>
#include "malloc.h"

/* retourne le pointeur sur break*/
void		*call_sbrk(size_t size, void **ptr_break)
{
  size_t	nb;

  if (size + SIZE_T_M <= SIZE_PAGE)
    {
      if ((*ptr_break = sbrk(SIZE_PAGE)) == (void *)-1)
	return (NULL);
      return (*ptr_break + SIZE_PAGE);
    }
  else
    {
      nb = ((size + SIZE_T_M) / SIZE_PAGE) + 1;
      if ((*ptr_break = sbrk(nb * SIZE_PAGE)) == (void *)-1)
	return (NULL);
      return (*ptr_break + (nb * SIZE_PAGE));
    }
}

/* retourne le pointeur sur la nouvelle meta créée*/
t_meta		*creat_first_meta(size_t size)
{
  t_meta	*new;
  void		*ptr_break;
  void		*trash;

  if ((g__ptr__ = sbrk(0)) == (void *)-1)
    return (NULL);
  if ((ptr_break = call_sbrk(size, &trash)) == NULL)
    return (NULL);
  new = g__ptr__;
  new->free = 0;
  new->size = size;
  new->next = NULL;
  new->prev = NULL;
  new->ptr_break = ptr_break;
  return (new);
}

/* retourne le pointeur sur la nouvelle meta créer */
t_meta		*creat_meta(size_t size)
{
  t_meta	*tmp;
  t_meta	*new;

  tmp = g__ptr__;
  while (tmp->next != NULL)
    {
      if (tmp->free == 1 && tmp->size >= size && 0 == (tmp->free = 0))
	{
	  if (tmp->size - size >= SIZE_T_M + SIZE_ALLIGNE)
	    {
	      new = (void *)tmp + SIZE_T_M + size;
	      new->size = tmp->size - size - SIZE_T_M;
	      new->next = tmp->next;
	      new->prev = tmp;
	      new->ptr_break = tmp->ptr_break;
	      tmp->next = new;
	      new->next->prev = new;
	      tmp->size = size;
	      free((void *)new + SIZE_T_M);
	    }
	  return (tmp);
	}
      tmp = tmp->next;
    }
  return (choise_to_creat_meta(size, tmp));
}

void		*malloc(size_t size)
{
  void		*tmp;
  size_t	nb;

  nb = 0;
  if (size == 0)
    return (NULL);
  while (nb < size)
    nb += SIZE_ALLIGNE;
  if (g__ptr__ == NULL)
    {
      if ((g__ptr__ = creat_first_meta(nb)) == NULL)
	return (NULL);
      tmp = g__ptr__;
    }
  else
    if ((tmp = creat_meta(nb)) == NULL)
      return (NULL);
  return (tmp + SIZE_T_M);
}
