#include "../include/push_swap.h"

void	sort_three_elemts_bott(t_ps *ps, t_stack *stack)
{
	if (stack->top->data < stack->top->next->data &&
			stack->top->next->data < stack->bott->data)
	{
		ft_putendl("11");
		move_all_to_stack_a(ps);
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
	move_all_to_stack_a(ps);
}

void	sort_three_elemts_top(t_ps *ps, t_stack *stack)
{
	if (stack->bott->data > stack->top->next->data &&
			stack->bott->data < stack->top->data)
	{
		ft_putendl("111");
		move_all_to_stack_a(ps);
		op_rra(ps);
		op_rra(ps);
		return ;
	}
	else if (stack->top->next->data < stack->top->data &&
			stack->top->next->data > stack->bott->data)
	{
		ft_putendl("222");
		op_rra(ps);
		op_sa(ps);
	}
	else if (stack->top->data < stack->bott->data &&
			stack->top->next->data > stack->bott->data)
	{
		ft_putendl("333");
		op_sa(ps);
	}
	else if (stack->top->data < stack->top->next->data &&
			stack->top->next->data < stack->bott->data)
	{
		ft_putendl("444");
		op_rra(ps);
	}
	else if (stack->top->data > stack->top->next->data &&
			stack->top->data < stack->bott->data)
	{
		ft_putendl("555");
		to_top_with_rr(ps);
		op_sa(ps);
	}
	else if (stack->top->data < stack->top->next->data &&
			stack->top->data > stack->bott->data)
	{
		ft_putendl("666");
		to_top_with_rr(ps);
	}
	move_all_to_stack_a(ps);
	op_rra(ps);
	op_rra(ps);
}

void	sort_three_elemts(t_ps *ps, t_stack *stack)
{
	if (stack->top->data < stack->top->next->data &&
			stack->top->data > stack->bott->data)
	{
		ft_putendl("1");
		move_all_to_stack_a(ps);
		op_rra(ps);
		return ;
	}
	else if (stack->top->data > stack->top->next->data &&
			stack->top->data < stack->bott->data)
	{
		ft_putendl("2");
		op_rra(ps);
		op_sa(ps);
	}
	else if (stack->top->data > stack->top->next->data &&
			stack->top->next->data > stack->bott->data)
	{
		ft_putendl("3");
		op_sa(ps);
	}
	else if (stack->bott->data > stack->top->next->data &&
			stack->bott->data < stack->top->data)
	{
		ft_putendl("4");
		op_rra(ps);
	}
	else if (stack->bott->data < stack->top->next->data &&
			stack->bott->data > stack->top->data)
	{
		ft_putendl("5");
		to_top_with_rr(ps);
		op_sa(ps);
	}
	else if (stack->top->data < stack->top->next->data &&
			stack->bott->data > stack->top->next->data)
	{
		ft_putendl("6");
		to_top_with_rr(ps);
	}
	move_all_to_stack_a(ps);
	op_rra(ps);
}

void	sort_two_elemts(t_ps *ps, t_stack *stack)
{
	ft_putendl("!!!!");
	if (stack->top->data == ps->sotr_arr[ps->count_arr - 1] && 
			stack->top->next->data == ps->sotr_arr[0])
	{
		ft_putendl("11111");
		move_all_to_stack_a(ps);
		op_rra(ps);
	}
	else if (stack->top->data == ps->sotr_arr[0] && 
			stack->top->next->data == ps->sotr_arr[ps->count_arr - 1])
	{
		ft_putendl("22222");
		op_sa(ps);
		move_all_to_stack_a(ps);
		op_rra(ps);
	}
	else if (stack->top->data == ps->sotr_arr[1] && 
			stack->top->next->data == ps->sotr_arr[0])
	{
		ft_putendl("33333");
		op_sa(ps);
		move_all_to_stack_a(ps);
		op_rra(ps);
		op_rra(ps);
	}
	else if (stack->top->data == ps->sotr_arr[0] && 
			stack->top->next->data == ps->sotr_arr[1])
	{
		ft_putendl("44444");
		move_all_to_stack_a(ps);
		op_rra(ps);
		op_rra(ps);
	}
	else if (stack->top->data == ps->sotr_arr[ps->count_arr - 1] && 
			stack->top->next->data == ps->sotr_arr[ps->count_arr - 2])
	{
		ft_putendl("55555");
		op_sa(ps);
		move_all_to_stack_a(ps);
	}
	else if (stack->top->data == ps->sotr_arr[ps->count_arr - 2] && 
			stack->top->next->data == ps->sotr_arr[ps->count_arr - 1])
	{
		ft_putendl("66666");
		move_all_to_stack_a(ps);
	}
}
