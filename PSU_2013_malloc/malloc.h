/*
** my_malloc.h for  in /home/lastru_g/Projet/malloc
**
** Made by lastrucci
** Login   <lastru_g@epitech.net>
**
** Started on  Mon Feb 10 13:19:59 2014 lastrucci
** Last update Sat Feb 15 14:22:16 2014 lastrucci
*/

#ifndef MY_MALLOC_H_
# define  MY_MALLOC_H_

#define SIZE_T_M sizeof(t_meta)
#define SIZE_PAGE (unsigned)getpagesize()
#define SIZE_ALLIGNE 8

typedef struct	s_meta
{
  char		free;		// 0 : non free ; 1 : free
  size_t	size;		// en octect, sans la taille de la meta
  struct s_meta	*next;		// meta suivante
  struct s_meta	*prev;		// meta precedante
  void		*ptr_break;	// pointeur sur break au moment ou l'on as créer la meta
}		t_meta;

	/*		global variable	*/
t_meta *g__ptr__;

	/*		show.c		*/

void		put_nbr_hexa_rec(unsigned int n);
void		put_nbr_hexa(unsigned int n);
void		put_nbr(unsigned int);

	/*		showmem.c		*/
void		showmem();

/* 	/\*		malloc.c		*\/ */
void		*malloc(size_t);
t_meta		*creat_first_meta(size_t);
t_meta		*creat_meta(size_t);
void		*call_sbrk(size_t, void **);

	/*		allocation.c		*/

t_meta		*creat_meta_by_alloc(size_t, t_meta *);
t_meta		*choise_to_creat_meta(size_t, t_meta *);

	/*		free			*/
void		free(void *);
t_meta		*check_whith_2_meta(t_meta *, t_meta *, char);

	/*		realloc.c		*/

char		verif_param(void *, size_t);
void		*verif_size_less(t_meta *, size_t);
void		*realloc_with_malloc(t_meta *, size_t);
void		*realloc(void *, size_t);

#endif
