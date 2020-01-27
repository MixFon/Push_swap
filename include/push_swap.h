#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include "../libft/libft.h"
#include "limits.h"

#define	STROP "rararbrrpbrraparrbrrrsasbss"

typedef struct		s_node
{
	int				data;
	size_t			number;
	struct s_node	*next;
}					t_node;

typedef struct		s_stack
{
	struct s_node	*top;
	struct s_node	*bott;
	struct s_node	*min;
	struct s_node	*el_to_top;
	size_t			count;
	int				bl_r;
	int				bl_rr;
}					t_stack;

typedef struct		s_ps
{
	t_stack			stack_a;
	t_stack			stack_b;
	int				*sotr_arr;
	int				count_arr;
}					t_ps;

void	op_pa(t_ps *ps);
void	op_pb(t_ps *ps);
void	op_ra(t_ps *ps);
void	op_rb(t_ps *ps);
void	op_rr(t_ps *ps);
void	op_rra(t_ps *ps);
void	op_rrb(t_ps *ps);
void	op_rrr(t_ps *ps);
void	op_sa(t_ps *ps);
void	op_sb(t_ps *ps);
void	op_ss(t_ps *ps);
void	move_all_to_stack_a(t_ps *ps);
void	to_top_with_rr(t_ps *ps);
void	sort_three_elemts(t_ps *ps, t_stack *stack);
void	sort_three_elemts_bott(t_ps *ps, t_stack *stack);
void	print_node(t_stack *stack_a, t_stack *stack_b);
void	print_sort_arr(t_ps *ps);
/*
** File shared_files/add_node.c
*/
void	init(t_ps *ps);
void	check_arg(char *arg);
void	search_dublicate(t_node *node, int data);
t_node	*create_node(int data, size_t *count);
void	add_node(t_ps *ps, int data);
/*
** File shared_files/processing_args.c
*/
int		check_number(char *arg);
void	infill_stack(t_ps *ps, int ac, char **av);
void	dell_arr(char ***arr);
void	bable_sort(t_ps *ps);
void	processing_args(t_ps *ps, int ac, char **av);
/*
** File shared_files/operations.c
*/
void	op_swap(t_stack *stack);
void	op_rotate(t_stack *stack);
void	op_reverse_rotate(t_stack *stack);
void	op_push(t_stack *one, t_stack *two);
#endif
