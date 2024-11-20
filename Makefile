# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paranha <paranha@student.42sp.org.br>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/27 18:03:10 by paranha           #+#    #+#              #
#    Updated: 2024/08/30 18:09:37 by paranha          ###   ########.org.br    #
#                                                                              #
# **************************************************************************** #

RED		=	\033[0;31m
GRN		=	\033[0;32m
YLW		=	\033[0;33m
BLU		=	\033[0;34m
MAG		=	\033[0;35m
CYA		=	\033[0;36m
WHT		=	\033[0;37m
RST		=	\033[0m

NAME	=	philo

FILES	=	main.c \
		simulation.c \
		eat_and_sleep.c \
		skynet.c \
		utils.c \

SRCDIR	=	src
SRC		=	$(FILES:%.c=$(SRCDIR)%.o)

OBJDIR	=	obj
OBJ		=	${FILES:%.c=$(OBJDIR)/%.o}

CC		=	cc
CFLGS	=	-Wextra -Wall -Werror -pthread -O3

INCLUDE	=	-I ./inc

all: $(NAME)

$(NAME): $(OBJ)
	rm -rf $(DEL)
	$(CC) $(CFLGS) $(OBJ) $(INCLUDE) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLGS) $(INCLUDE) -c $< -o $@
	@echo "${GRN}Compile $@ DONE${RST}"

clean:
	@rm -rf $(OBJDIR)
	@echo "${RED}CLEAN:	Objects $(OBJ) DELETED${RST}"

fclean: clean
	@rm -rf $(NAME)
	@echo "${RED}FCLEAN $(NAME) DELETED${RST}"

re: clean all

.PHONY: all, clean, fclean, re

