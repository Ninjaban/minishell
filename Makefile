#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcarra <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/16 09:04:55 by jcarra            #+#    #+#              #
#    Updated: 2016/11/17 11:18:50 by jcarra           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		=	minishell

SRC			=	ft_exec.c \
				ft_gestion_error.c \
				ft_error.c \
				ft_parsing.c \
				ft_shell.c \
				ft_main.c

LIB			=	libft.a

DIRSRC		=	sources/
DIRINC		=	include/
DIRLIB		=	library/

SRCS		=	$(SRC:%=$(DIRSRC)%)
OBJS		=	$(SRC:.c=.o)
LIBS		=	$(LIB:%=$(DIRLIB)%)

CFLAGS		=	-Wall -Wextra -Werror -I./$(DIRINC) -I./$(DIRLIB)$(DIRINC)

CC			=	gcc
RM			=	rm -f
ECHO		=	printf
MAKE		=	make -C


all		:		$(NAME)
			   	@$(ECHO) ''

$(NAME)	:
				@$(MAKE) $(DIRLIB)
				@$(CC) $(CFLAGS) -c $(SRCS)
				@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)
				@$(ECHO) '\033[32m> Compiled\n\033[0m'

clean	:
				@$(MAKE) $(DIRLIB) clean
				@$(RM) $(OBJS)
				@$(ECHO) '\033[31m> Directory cleaned\n\033[0m'

fclean	:		clean
				@$(MAKE) $(DIRLIB) fclean
				@$(RM) $(NAME)
				@$(ECHO) '\033[31m> Remove executable\n\033[0m'

re		:		fclean all

.PHONY	:		all clean fclean re
