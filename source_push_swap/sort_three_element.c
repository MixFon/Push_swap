#include "../include/push_swap.h"

void	sort_three_elemts_bott(t_ps *ps, t_stack *stack)
{
	if (stack->top->data < stack->top->next->data &&
			stack->top->next->data < stack->bott->data)
	{
		ft_putendl("11");
		return ;
	}
	else if (stack->bott->data > stack->top->data &&
			stack->bott->data < stack->top->next->data)
	{
		ft_putendl("22");
		op_rra(ps);
		op_sa(ps);
	}
	else if (stack->top->data > stack->top->next->data &&
			stack->top->data < stack->bott->data)
	{
		ft_putendl("33");
		op_sa(ps);
	}
	else if (stack->top->data < stack->top->next->data &&
			stack->top->data > stack->bott->data)
	{
		ft_putendl("44");
		op_rra(ps);
	}
	else if (stack->bott->data > stack->top->next->data &&
			stack->bott->data < stack->top->data)
	{
		ft_putendl("55");
		to_top_with_rr(ps);
	}
	else if (stack->top->next->data < stack->top->data &&
			stack->top->next->data > stack->bott->data)
	{
		ft_putendl("66");
		op_sa(ps);
		op_rra(ps);
	}
}
