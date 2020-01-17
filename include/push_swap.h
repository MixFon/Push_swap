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
}					t_stack;

typedef struct		s_mid
{
	int				item;
	int				num_item_sort;
}					t_mid;

typedef struct		s_ps
{
	t_stack			stack_a;
	t_stack			stack_b;
	int				*sotr_arr;
	int				count_arr;
	t_mid			mid[3];
}					t_ps;

#endif
