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

void	sort_two_element(t_ps *ps, t_stack *stack)
{
	if (stack->top->data > stack->top->next->data)
		op_sa(ps);
}

void	sort_elemts(t_ps *ps, t_stack *stack)
{
	if (stack->count == 1)
		return;
	else if (stack->count == 2)
		sort_two_element(ps, stack);
	else if (stack->count == 3)
		sort_three_elemts_bott(ps, stack);

}
