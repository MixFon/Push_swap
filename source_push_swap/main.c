#include "../include/push_swap.h"

void	recount_number_stack(t_node *node)
{
	size_t	number;

	number = -1;
	while (node)
	{
		node->number = ++number;
		node = node->next;
	}
}

void	op_pa(t_ps *ps)
{
	op_push(&ps->stack_b, &ps->stack_a);
	ft_putendl("pa");
}

void	op_pb(t_ps *ps)
{
	op_push(&ps->stack_a, &ps->stack_b);
	ft_putendl("pb");
}

void	op_ra(t_ps *ps)
{
	op_rotate(&ps->stack_a);
	ft_putendl("ra");
}

void	op_rb(t_ps *ps)
{
	op_rotate(&ps->stack_b);
	ft_putendl("rb");
}

void	op_rr(t_ps *ps)
{
	op_rotate(&ps->stack_a);
	op_rotate(&ps->stack_b);
	ft_putendl("rr");
}

void	op_rra(t_ps *ps)
{
	op_reverse_rotate(&ps->stack_a);
	ft_putendl("rra");
}

void	op_rrb(t_ps *ps)
{
	op_reverse_rotate(&ps->stack_b);
	ft_putendl("rrb");
}

void	op_rrr(t_ps *ps)
{
	op_reverse_rotate(&ps->stack_a);
	op_reverse_rotate(&ps->stack_b);
	ft_putendl("rrr");
}

void	op_sa(t_ps *ps)
{
	op_swap(&ps->stack_a);
	ft_putendl("sa");
}

void	op_sb(t_ps *ps)
{
	op_swap(&ps->stack_b);
	ft_putendl("sb");
}

void	op_ss(t_ps *ps)
{
	op_swap(&ps->stack_a);
	op_swap(&ps->stack_b);
	ft_putendl("ss");
}

void	to_top_with_rr(t_ps *ps)
{
	if (ps->stack_b.bl_rr == 1)
	{
		op_rr(ps);
		ps->stack_b.bl_rr = 0;
	}
	else
		op_ra(ps);
}

void	move_all_to_stack_a(t_ps *ps)
{
	while (ps->stack_b.count > 0)
		op_pa(ps);
}

void	determine_minimal_el(t_ps *ps)
{
	t_node *node;

	node = ps->stack_a.top;
	ps->stack_a.min = node;
	while (node)
	{
		if (ps->stack_a.min->data > node->data)
			ps->stack_a.min = node;
		node = node->next;
	}
	/*
	ft_printf("min->data = [%d] min->number = [%d]\n", ps->stack_a.min->data,
			ps->stack_a.min->number);
	*/
}

int		is_cycle_sort(t_ps *ps)
{
	t_node	*node;

	determine_minimal_el(ps);
	node = ps->stack_a.top;
	while (node && node->next)
	{
	//	ft_printf("node->data = [%d]\n", node->data);
		if (node->data > node->next->data && node->next != ps->stack_a.min)
			return (0);
		node = node->next;
	}
	if (ps->stack_a.top == ps->stack_a.min)
		return (1);
	if (ps->stack_a.top->data < ps->stack_a.bott->data)
		return (0);
	return (1);
}

int		count_steps_to_top(t_stack *stack, int data)
{
	t_node *node;
	int		res;

	res = 0;
	node = stack->top;
	while (node)
	{
		if (node->data == data)
		{
			if (node->number <= stack->count / 2) 
			{
				res = node->number;
				stack->bl_r = 1;
				stack->bl_rr = 0;
			}
			else
			{
				res = (stack->count - node->number);
				stack->bl_r = 0;
				stack->bl_rr = 1;
			}
			stack->el_to_top = node;
			return (res);
		}
		node = node->next;
	}
	return (0);
}

int		count_steps(t_ps *ps, int data)
{
	int		steps;
	t_node	*node;

	node = ps->stack_a.top;
	steps = count_steps_to_top(&ps->stack_b, data);
	if (data < ps->stack_a.top->data && data > ps->stack_a.bott->data)
	{
	//	ft_putendl("aa");
		steps += count_steps_to_top(&ps->stack_a, node->data);
		return (steps + 1);
	}
	while (node->next)
	{
		if (node->data < data &&
				(node->next->data > data || node->next == ps->stack_a.min))
		{
	//		ft_putendl("dd");
			steps += count_steps_to_top(&ps->stack_a, node->next->data);
			break;
		}
		node = node->next;
	}
	if (node->next == NULL)
		count_steps_to_top(&ps->stack_a, ps->stack_a.min->data);
	//ft_putendl("cc");
	//count_steps_to_top(&ps->stack_a, ps->stack_a.top->data);
	return (steps + 1);
}

t_node	*search_min_el(t_ps *ps)
{
	t_node	*node;
	t_node	*min_el;
	int		steps;
	int		tmp;

	node = ps->stack_b.top;
	min_el = node;
	steps = ps->stack_b.count;
	while (node)
	{
		tmp = count_steps(ps, node->data);
		if (steps > tmp)
		{
			steps = tmp;
			min_el = node;
		}
		/*
		ft_printf("data = [%d] steps = [%d]\n", node->data,
				tmp);
				*/
		node = node->next;
	}
	count_steps(ps, min_el->data);
	/*
	ft_printf("min data = [%d] steps = [%d]\n", min_el->data,
			count_steps(ps, min_el->data));
	ft_printf("stack_a.min = [%d]\n", ps->stack_a.min->data);
	ft_printf("el_to_top A  = [%d]\n", ps->stack_a.el_to_top->data);
	ft_printf("el_to_top B  = [%d]\n", ps->stack_b.el_to_top->data);
	*/
	return (min_el);
}

void	move_min_el(t_ps *ps)
{
	while (ps->stack_a.bl_r || ps->stack_a.bl_rr ||
			ps->stack_b.bl_r || ps->stack_b.bl_rr)
	{
		if (ps->stack_a.top == ps->stack_a.el_to_top)
		{
			ps->stack_a.bl_r = 0;
			ps->stack_a.bl_rr = 0;
		}
		if (ps->stack_b.top == ps->stack_b.el_to_top)
		{
			ps->stack_b.bl_r = 0;
			ps->stack_b.bl_rr = 0;
		}
		if (ps->stack_a.bl_r && ps->stack_b.bl_r)
			op_rr(ps);
		else if (ps->stack_a.bl_rr && ps->stack_b.bl_rr)
			op_rrr(ps);
		else if (ps->stack_a.bl_rr)
			op_rra(ps);
		else if (ps->stack_a.bl_r)
			op_ra(ps);
		else if (ps->stack_b.bl_r)
			op_rb(ps);
		else if (ps->stack_b.bl_rr)
			op_rrb(ps);
	}
}

void	empty_stack_b(t_ps *ps)
{
	t_node *min_el;

	while (ps->stack_b.count > 0)
	{
		determine_minimal_el(ps);
		min_el = search_min_el(ps);
		move_min_el(ps);
		op_pa(ps);
		recount_number_stack(ps->stack_a.top);
		recount_number_stack(ps->stack_b.top);
		//print_node(&ps->stack_a, &ps->stack_b);
	}
}
void	final_sort(t_ps *ps)
{
	if (ps->stack_a.min->data <= ps->stack_a.count / 2)
		while (ps->stack_a.top != ps->stack_a.min)
			op_ra(ps);
	else 
		while (ps->stack_a.top != ps->stack_a.min)
			op_rra(ps);
}

void	algoritm(t_ps *ps)
{
	//print_node(&ps->stack_a, &ps->stack_b);
	//ft_printf("is cycle = [%d]\n", is_cycle_sort(ps));
	while (!is_cycle_sort(ps) && ps->stack_a.count > 3)
	{
		op_pb(ps);
		recount_number_stack(ps->stack_a.top);
		recount_number_stack(ps->stack_b.top);
	}
	//print_node(&ps->stack_a, &ps->stack_b);
	if (!is_cycle_sort(ps) && ps->stack_b.count != 0)
		sort_three_elemts_bott(ps, &ps->stack_a);
	//print_node(&ps->stack_a, &ps->stack_b);
	empty_stack_b(ps);
	final_sort(ps);
	delete_stack(&ps->stack_a);
	delete_stack(&ps->stack_b);
	//print_node(&ps->stack_a, &ps->stack_b);
	//ft_printf("is cycle = [%d]\n", is_cycle_sort(ps));
}

int		main(int ac, char **av)
{
	t_ps	ps;

	if (ac < 2)
		sys_err("To few arguments.\n");
	init(&ps);
	processing_args(&ps, ac, av);
	algoritm(&ps);
	return (0);
}
