/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node_add.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 11:34:30 by widraugr          #+#    #+#             */
/*   Updated: 2020/01/30 11:40:44 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	stack_is_sort(t_ps *ps)
{
	t_node *node;

	node = ps->stack_a.top;
	while (node && node->next != NULL)
	{
		if (node->data > node->next->data)
		{
			//print_node(&ps->stack_a, &ps->stack_b);
			sys_err("KO\n");
		}
		node = node->next;
	}
	if (ps->stack_b.count != 0)
		sys_err("KO\n");
	//print_node(&ps->stack_a, &ps->stack_b);
	ft_putendl("OK");
}

int		work_operators(t_ch *ch)
{
	if (ch->iter == NULL)
		return (0);
	work_perations(&ch->ps, ch->iter->op);
	if (ch->flag_v)
	{
		clear_image(ch);
		mlx_put_stacks(ch);
	}
	ch->iter = ch->iter->next;
	if (ch->iter == NULL)
	{
		stack_is_sort(&ch->ps);
		delete_stack(&ch->ps.stack_a);
		delete_stack(&ch->ps.stack_b);
		if (ch->flag_v)
			return (0);
		exit(0);
		//sys_err("Done!\n");
	}
	return (0);
}

t_op	*create_node_op(char *line)
{
	t_op *node;

	if (!(node = (t_op*)malloc(sizeof(t_op))))
		sys_err("Error malloc\n");
	strcpy(node->op, line);
	node->next = NULL;
	return (node);
}
