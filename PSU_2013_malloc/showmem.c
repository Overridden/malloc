/*
** showmem.c for showmem in /home/nguye_1/rendu/PSU_2014_malloc
**
** Made by Alexandre NGUYEN
** Login   <nguye_1@epitech.net>
**
** Started on  Fri Feb 14 15:13:31 2014 Alexandre NGUYEN
** Last update Sat Feb 15 16:08:56 2014 Alexandre NGUYEN
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "./malloc.h"

void		showmem()
{
  t_meta	*tmp;
  int		i;

  tmp = g__ptr__;
  i = 0;
  if (!tmp)
    printf("No elements\n");
  while (tmp)
    {
      printf("Addr:\033[0;33m %p\033[0m\tsize:\033[0;33m "
	     "%d%s\t\033[0mfree? %s\n",
	     (void *)tmp + SIZE_T_M, (unsigned int)(tmp->size),
	     (tmp->size < 100 ? ".0" : ""),
	     (tmp->free == 0 ? "\033[1;31mno\033[0m" : "\033[1;32myes\033[0m"));
      tmp = tmp->next;
      i += 1;
    }
  printf("Number of elements: \033[1m%d\033[0m\n\n", i);
  return ;
}
