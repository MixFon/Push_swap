/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 11:24:59 by widraugr          #+#    #+#             */
/*   Updated: 2020/01/30 11:35:56 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include "../libft/libft.h"
#include "limits.h"
#include "../minilibx_macos/mlx.h"

# define STROP		"rararbrrpbrraparrbrrrsasbss"
# define WIDTH		1500
# define HEIGHT		1200

# define HALFWID	750
# define HALFHEI	500

# define STARTY		100

# define ABS(N) ((N<0)?(-N):(N))

typedef struct		s_node
{
	int				data;
	int				number;
	struct s_node	*next;
}					t_node;

typedef struct		s_stack
{
	struct s_node	*top;
	struct s_node	*bott;
	struct s_node	*min;
	struct s_node	*el_to_top;
	int				count;
	int				bl_r;
	int				bl_rr;
}					t_stack;

typedef struct		s_ps
{
	t_stack			stack_a;
	t_stack			stack_b;
}					t_ps;

typedef struct		s_op
{
	char			op[10];
	size_t			number;
	struct s_op		*next;
}					t_op;

typedef struct		s_ch
{
	struct s_ps		ps;
	struct s_op		*op;
	struct s_op		*iter;
	void			*mlx;
	void			*window;
	void			*img_ptr;
	int				bits_adr;
	int				size_adr;
	int				endian;
	char			*data_adr;
}					t_ch;

typedef struct	s_coor
{
	int			x;
	int			y;
	int			color;
}				t_coor;

void	sort_three_elemts(t_ps *ps, t_stack *stack);
void	print_node(t_stack *stack_a, t_stack *stack_b);
void	print_sort_arr(t_ps *ps);
/*
** File shared_files/add_node.c
*/
void	init(t_ps *ps);
void	check_arg(char *arg);
void	search_dublicate(t_node *node, int data);
t_node	*create_node(int data, int *count);
void	add_node(t_ps *ps, int data);
/*
** File shared_files/processing_args.c
*/
int		check_number(char *arg);
void	infill_stack(t_ps *ps, char **av);
void	dell_arr(char ***arr);
void	delete_stack(t_stack *stack);
void	processing_args(t_ps *ps, int ac, char **av);
/*
** File shared_files/operations.c
*/
void	op_swap(t_stack *stack);
void	op_rotate(t_stack *stack);
void	op_reverse_rotate(t_stack *stack);
void	op_push(t_stack *one, t_stack *two);
/*
** File source_push_swap/pa_pb_ra_rb_rr.c
*/
void	op_pa(t_ps *ps);
void	op_pb(t_ps *ps);
void	op_ra(t_ps *ps);
void	op_rb(t_ps *ps);
void	op_rr(t_ps *ps);
/*
** File source_push_swap/rra_rrb_rrr_sa_sb.c
*/
void	op_rra(t_ps *ps);
void	op_rrb(t_ps *ps);
void	op_rrr(t_ps *ps);
void	op_sa(t_ps *ps);
void	op_sb(t_ps *ps);
/*
** File source_push_swap/determine_minimal_el.c
*/
void	op_ss(t_ps *ps);
void	recount_number_stack(t_node *node);
void	to_top_with_rr(t_ps *ps);
void	move_all_to_stack_a(t_ps *ps);
void	determine_minimal_el(t_ps *ps);
/*
** File source_push_swap/search_min_el.c
*/
void	move_min_el(t_ps *ps);
void	stack_bl(t_stack *stack, int bl_r, int bl_rr);
int		count_steps_to_top(t_stack *stack, int data);
int		count_steps(t_ps *ps, int data);
t_node	*search_min_el(t_ps *ps);
/*
** File source_push_swap/sort_elemts.c
*/
void	sort_three_elemts_bott(t_ps *ps, t_stack *stack);
void	sort_two_element(t_ps *ps, t_stack *stack);
void	sort_elemts(t_ps *ps, t_stack *stack);
/*
** File source_push_swap/main.c
*/
int		is_cycle_sort(t_ps *ps);
void	empty_stack_b(t_ps *ps);
void	final_sort(t_ps *ps);
void	algoritm(t_ps *ps);
int		main(int ac, char **av);
/*
** File source_checker/ft_draw_line.c
*/
void	init_ch(t_ch *ch);
void	check(char *line);
t_coor	ft_draw_line_source(t_coor *delta, t_coor *sign, t_coor point1, t_coor point2);
void	put_pixel_adr(t_ch *ch, t_coor point);
void	ft_draw_line(t_ch *ch, t_coor point1, t_coor point2, int color);
/*
** File source_checker/work_perations.c
*/
void	clear_image(t_ch *fdf);
void	put_stack(t_ch *ch, t_stack *stack, int start_x);
void	mlx_put_stacks(t_ch *ch);
void	work_perations_next(t_ps *ps, char *line);
void	work_perations(t_ps *ps, char *line);
/*
** File source_checker/work_perations.c
*/
void	stack_is_sort(t_ps *ps);
int		work_operators(t_ch *ch);
t_op	*create_node_op(char *line);
#endif
