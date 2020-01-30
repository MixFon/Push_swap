/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 11:48:31 by widraugr          #+#    #+#             */
/*   Updated: 2020/01/30 11:49:20 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	init(t_ps *ps)
{
	ps->stack_a.top = NULL;
	ps->stack_a.bott = NULL;
	ps->stack_a.el_to_top = NULL;
	ps->stack_a.min = NULL;
	ps->stack_a.count = 0;
	ps->stack_a.bl_r = 0;
	ps->stack_a.bl_rr = 0;
	ps->stack_b.top = NULL;
	ps->stack_b.bott = NULL;
	ps->stack_b.el_to_top = NULL;
	ps->stack_b.min = NULL;
	ps->stack_b.count = 0;
	ps->stack_b.bl_r = 0;
	ps->stack_b.bl_rr = 0;
}

void	check_arg(char *arg)
{
	int neg;
	int plus;

	neg = 0;
	plus = 0;
	while (*arg != '\0')
	{
		if (!ft_isdigit(*arg) && *arg != '-' && *arg != '+')
			sys_err("Error arguments.\n");
		if (*arg == '-')
			neg++;
		else if (*arg == '+')
			plus++;
		arg++;
	}
	if (neg + plus > 1)
		sys_err("Error arguments.\n");
}

void	search_dublicate(t_node *node, int data)
{
	while (node)
	{
		if (node->data == data)
			sys_err("Found dublicate.\n");
		node = node->next;
	}
}

t_node	*create_node(int data, int *count)
{
	t_node *node;

	if (!(node = (t_node*)malloc(sizeof(t_node))))
		sys_err("Error malloc\n");
	node->next = NULL;
	node->data = data;
	node->number = *count;
	(*count)++;
	return (node);
}

void	add_node(t_ps *ps, int data)
{
	t_node *tmp;

	if (ps->stack_a.top == NULL)
	{
		ps->stack_a.top = create_node(data, &ps->stack_a.count);
		ps->stack_a.bott = ps->stack_a.top;
		return ;
	}
	search_dublicate(ps->stack_a.top, data);
	tmp = create_node(data, &ps->stack_a.count);
	ps->stack_a.bott->next = tmp;
	ps->stack_a.bott = tmp;
}
