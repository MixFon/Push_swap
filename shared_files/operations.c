/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 11:49:32 by widraugr          #+#    #+#             */
/*   Updated: 2020/01/30 11:50:11 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	print_node(t_stack *stack_a, t_stack *stack_b)
{
	t_node *node_a;
	t_node *node_b;

	node_a = stack_a->top;
	node_b = stack_b->top;
	ft_printf("\nstack_a = {%d}\n", stack_a->count);
	ft_printf("stack_b = {%d}\n", stack_b->count);
	while (node_a || node_b)
	{
		if (node_a)
			ft_printf("{%d}\t", node_a->data);
		else
			ft_printf("{%c}\t", ' ');
		if (node_b)
			ft_printf("{%d}\n", node_b->data);
		else
			ft_printf("{%c}\n", ' ');
		if (node_a)
			node_a = node_a->next;
		if (node_b)
			node_b = node_b->next;
	}
}

void	op_swap(t_stack *stack)
{
	t_node *node;

	if (stack->count < 2)
		return ;
	node = stack->top->next;
	stack->top->next = node->next;
	node->next = stack->top;
	stack->top = node;
	if (stack->top == stack->bott)
		stack->bott = stack->top->next;
}

void	op_rotate(t_stack *stack)
{
	t_node *node;

	if (stack->count < 2)
		return ;
	node = stack->top;
	stack->top = stack->top->next;
	stack->bott->next = node;
	stack->bott = node;
	node->next = NULL;
}

void	op_reverse_rotate(t_stack *stack)
{
	t_node *node;

	if (stack->count < 2)
		return ;
	node = stack->top;
	while (node->next != stack->bott)
		node = node->next;
	node->next = NULL;
	stack->bott->next = stack->top;
	stack->top = stack->bott;
	stack->bott = node;
}

void	op_push(t_stack *one, t_stack *two)
{
	t_node *node;

	if (one->count == 0)
		return ;
	node = one->top;
	one->top = one->top->next;
	one->count--;
	node->next = two->top;
	two->top = node;
	two->count++;
	if (two->count == 1)
		two->bott = two->top;
}
