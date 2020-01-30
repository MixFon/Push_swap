# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: widraugr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/29 13:07:44 by widraugr          #+#    #+#              #
#    Updated: 2020/01/30 12:48:50 by widraugr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAMEPS = push_swap

NAMECH = checker

LIBDIR = ./libft

PS_C = sort_three_element.c\
	   determine_minimal_el.c\
	   pa_pb_ra_rb_rr.c\
	   search_min_el.c\
	   rra_rrb_rrr_sa_sb.c\
	   main.c

CH_C = checker.c\
	   create_node_add.c\
	   ft_drow_line.c\
	   work_operations.c

SH_C = add_node.c\
	   processing_arg.c\
	   operations.c

FLAGS = -Wall -Wextra -Werror -I libft -I include -I ./minilibx_macos

HFILE = -I libft -I ./include -I ./minilibx_macos 
 
FLAGSMLX = -L ./minilibx_macos -lmlx -framework OpenGL -framework AppKit

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
	make -C $(LIBDIR)
	gcc $(FLAGS) $(OBJCH) $(OBJSH) $(FLAGSMLX) $(FLIB) -o $(NAMECH)
	gcc $(FLAGS) $(OBJ) $(OBJSH) $(FLIB) -o $(NAMEPS)

$(DIROBJ)%.o : $(DIRPS)%.c
	gcc -g $(FLAGS) -c $< -o $@

$(DIROBJ)%.o : $(DIRCH)%.c
	gcc -g $(FLAGS) -c $< -o $@

$(DIROBJ)%.o : $(DIRSH)%.c
	gcc -g $(FLAGS) -c $< -o $@

$(DIROBJ):
	mkdir -p $(DIROBJ)

clean:
	/bin/rm -rf $(DIROBJ)
	
fclean: clean
	/bin/rm -f $(NAMEPS)
	/bin/rm -f $(NAMECH)
	make fclean -C $(LIBDIR)
	
re: fclean all 
