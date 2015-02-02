/*
** my_realloc.c for  in /home/lastru_g/rendu/test
**
** Made by lastrucci
** Login   <lastru_g@epitech.net>
**
** Started on  Thu Feb 13 20:32:29 2014 lastrucci
** Last update Sat Feb 15 15:27:16 2014 lastrucci
*/

#include <string.h>
#include <unistd.h>
#include "./malloc.h"

char		verif_param(void *ptr, size_t size)
{
  t_meta	*tmp;
  char		exit;

  exit = 0;
  tmp = g__ptr__;
  while (tmp)
    {
      if (tmp == ptr)
  	exit = 1;
      tmp = tmp->next;
    }
  if (exit == 0)
    return (0);
  if (size == 0)
    {
      free(ptr + SIZE_T_M);
      return (0);
    }
  return (1);
}

void		*verif_size_less(t_meta *ptr, size_t size)
{
  t_meta	*new;

  if (size > ptr->size)
    return (NULL);
  if (size == ptr->size)
    return ((void *)ptr);
  if (ptr->size - size > SIZE_T_M)
    {
      new = (void *)ptr + SIZE_T_M + size;
      new->size = ptr->size - size - SIZE_T_M;
      new->next = ptr->next;
      new->prev = ptr;
      new->ptr_break = ptr->ptr_break;
      if (ptr->next)
	ptr->next->prev = new;
      ptr->next = new;
      free((void *)new + SIZE_T_M);
    }
  else
    {
      ptr->size = size;
      return (ptr);
    }
  ptr->size = size;
  return (new);
}

void		*realloc_with_malloc(t_meta *tmp, size_t size)
{
  void		*new;

  if ((new = malloc(size)) == NULL)
    return (NULL);
  memcpy(new, (void *)tmp + SIZE_T_M, tmp->size);
  tmp->free = 1;
  return (new);
}

void		*realloc(void *ptr, size_t size)
{
  void		*new;
  t_meta	*tmp;
  size_t	nb;

  nb = 0;
  ptr -= SIZE_T_M;
  tmp = (t_meta *)ptr;
  if (verif_param(tmp, size) == 0)
    return (NULL);
  while (nb < size)
    nb += 512;
  if ((new = verif_size_less(tmp, nb)) != NULL)
    return (new + SIZE_T_M);
  if (tmp->next)
    if (tmp->next->free == 1 && (tmp->size + tmp->next->size + SIZE_T_M) >= nb)
      if ((void *)tmp + SIZE_T_M + tmp->size == tmp->next)
	{
	  tmp->size += tmp->next->size + SIZE_T_M;
	  tmp->ptr_break = tmp->next->ptr_break;
	  tmp->next = tmp->next->next;
	  if (tmp->next)
	    tmp->next->prev = tmp;
	  return (verif_size_less(tmp, nb));
	}
  return (realloc_with_malloc(tmp, nb));
}
