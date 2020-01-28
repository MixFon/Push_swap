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

PS_C = main.c\
		 sort_three_element.c

CH_C = checker.c

SH_C = add_node.c\
	   processing_arg.c\
	   operations.c


# -Wall -Wextra -Werror 
FLAGS = -I libft -I include  
#-Wall -Wextra -Werror 
FLAGSMLX = -I minilibx_macos -L minilibx_macos -lmlx -framework OpenGL -framework AppKit

FLIB = -L ./libft -lftprintf 

DIRPS = ./source_push_swap/

DIRCH = ./source_checker/

DIRSH = ./shared_files/

VPATH = $(DIROBJ)

DIROBJ = ./obj/

OBJ = $(addprefix $(DIROBJ), $(PS_C:.c=.o))

OBJCH = $(addprefix $(DIROBJ), $(CH_C:.c=.o))

OBJSH = $(addprefix $(DIROBJ), $(SH_C:.c=.o))


all : $(NAMEPS) $(NAMECH)

$(NAMEPS): $(DIROBJ) $(OBJSH) $(OBJCH) $(OBJ) 
#	make -C $(LIBDIR)
	gcc $(FLAGS) $(OBJ) $(OBJSH) $(FLIB) -o $(NAMEPS)
	gcc $(FLAGS) $(FLAGSMLX) $(OBJCH) $(OBJSH) $(FLIB) -o $(NAMECK)
	make clean -C $(LIBDIR)

$(DIROBJ)%.o : $(DIRPS)%.c
	gcc -g $(FLAGS) -c $< -o $@

$(DIROBJ)%.o : $(DIRCH)%.c
	gcc -g $(FLAGS) $(FLAGSMLX) -c $< -o $@

$(DIROBJ)%.o : $(DIRSH)%.c
	gcc -g $(FLAGS) -c $< -o $@

$(DIROBJ):
	mkdir -p $(DIROBJ)

clean:
	/bin/rm -rf $(DIROBJ)
	
fclean: clean
	/bin/rm -f $(NAMEPS)
#	make fclean -C $(LIBDIR)
	
re: fclean all 
