#include "../include/push_swap.h"

void	sort_three_elemts_bott(t_ps *ps, t_stack *stack)
{
	if (stack->top->data < stack->top->next->data &&
			stack->top->next->data < stack->bott->data)
		return ;
	else if (stack->bott->data > stack->top->data &&
			stack->bott->data < stack->top->next->data)
	{
		op_rra(ps);
		op_sa(ps);
	}
	else if (stack->top->data > stack->top->next->data &&
			stack->top->data < stack->bott->data)
		op_sa(ps);
	else if (stack->top->data < stack->top->next->data &&
			stack->top->data > stack->bott->data)
		op_rra(ps);
	else if (stack->bott->data > stack->top->next->data &&
			stack->bott->data < stack->top->data)
		to_top_with_rr(ps);
	else if (stack->top->next->data < stack->top->data &&
			stack->top->next->data > stack->bott->data)
	{
		op_sa(ps);
		op_rra(ps);
	}
}
