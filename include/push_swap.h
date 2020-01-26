#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include "../libft/libft.h"
#include "limits.h"

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
	size_t			count;
	int				bl_ss;
	int				bl_rr;
}					t_stack;

typedef struct		s_ps
{
	t_stack			stack_a;
	t_stack			stack_b;
	int				*sotr_arr;
	int				count_arr;
	int				only_bott;
	int				only_top;
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

#endif
