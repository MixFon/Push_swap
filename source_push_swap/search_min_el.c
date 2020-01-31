/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_min_el.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 10:44:13 by widraugr          #+#    #+#             */
/*   Updated: 2020/01/30 11:47:23 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	stack_bl(t_stack *stack, int bl_r, int bl_rr)
{
	stack->bl_r = bl_r;
	stack->bl_rr = bl_rr;
}

int		count_steps_to_top(t_stack *stack, int data)
{
	t_node	*node;
	int		res;

	res = 0;
	node = stack->top;
	recount_number_stack(stack->top);
	while (node)
	{
		if (node->data == data)
		{
			if (node->number <= (stack->count / 2))
			{
				res = node->number;
				stack_bl(stack, 1, 0);
			}
			else
			{
				res = (stack->count - node->number);
				stack_bl(stack, 0, 1);
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
		steps += count_steps_to_top(&ps->stack_a, node->data);
		return (steps + 1);
	}
	while (node->next)
	{
		if (node->data < data &&
				(node->next->data > data || node->next == ps->stack_a.min))
		{
			steps += count_steps_to_top(&ps->stack_a, node->next->data);
			break ;
		}
		node = node->next;
	}
	if (node->next == NULL)
		count_steps_to_top(&ps->stack_a, ps->stack_a.min->data);
	return (steps + 1);
}

void	move_min_el(t_ps *ps)
{
	while (ps->stack_a.bl_r || ps->stack_a.bl_rr ||
			ps->stack_b.bl_r || ps->stack_b.bl_rr)
	{
		if (ps->stack_a.top == ps->stack_a.el_to_top)
			stack_bl(&ps->stack_a, 0, 0);
		if (ps->stack_b.top == ps->stack_b.el_to_top)
			stack_bl(&ps->stack_b, 0, 0);
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

t_node	*search_min_el_b(t_ps *ps)
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
		node = node->next;
	}
	count_steps(ps, min_el->data);
	return (min_el);
}
