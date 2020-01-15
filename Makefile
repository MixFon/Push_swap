# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: widraugr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/29 13:07:44 by widraugr          #+#    #+#              #
#    Updated: 2019/12/06 10:10:28 by widraugr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAMEPS = push_swap
NAMECK = checker

LIBDIR = ./libft


FILE_C = main.c

# -Wall -Wextra -Werror 
FLAGS = -I libft -I include  

FLIB = -L ./libft -lftprintf 

DIRPS = ./source_push_swap/

VPATH = $(DIROBJ)

DIROBJ = ./obj/

OBJ = $(addprefix $(DIROBJ), $(FILE_C:.c=.o))

all : $(NAMEPS)

$(NAMEPS): $(DIROBJ) $(OBJ) 
#	make -C $(LIBDIR)
	gcc $(FLAGS) $(OBJ) $(FLIB) -o $(NAMEPS)
	make clean -C $(LIBDIR)

$(DIROBJ)%.o : $(DIRPS)%.c
	gcc -g $(FLAGS) -c $< -o $@

$(DIROBJ):
	mkdir -p $(DIROBJ)

clean:
	/bin/rm -rf $(DIROBJ)
	
fclean: clean
	/bin/rm -f $(NAMEPS)
#	make fclean -C $(LIBDIR)
	
re: fclean all 
