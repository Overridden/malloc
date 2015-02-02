##
## Makefile for malloc in /home/nguye_1/rendu/PSU_2014_malloc/nguye_1
## 
## Made by Alexandre NGUYEN
## Login   <nguye_1@epitech.net>
## 
## Started on  Sat Feb 15 12:41:03 2014 Alexandre NGUYEN
## Last update Sat Feb 15 15:38:25 2014 lastrucci
##

CC	=	gcc

SRC	=	malloc.c	\
		free.c		\
		realloc.c	\
		allocation.c	\
		showmem.c

RM	=	rm -f

NAME	=	libmy_malloc_$(HOSTTYPE).so

CFLAGS	=	-fPIC -Wall -Wextra

LFLAGS	=	-shared

OBJ	=	$(SRC:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(LFLAGS) $(OBJ) -o $(NAME)
		ln -s $(NAME) libmy_malloc.so

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)
		$(RM) libmy_malloc.so

re:		fclean all
