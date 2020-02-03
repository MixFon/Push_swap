/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node_add.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 11:34:30 by widraugr          #+#    #+#             */
/*   Updated: 2020/02/03 09:10:22 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	check_flag_v(t_ch *ch, int ac, char **av)
{
	int a;

	ch->flag_v = 0;
	ch->op = NULL;
	a = ac;
	if (!ft_strncmp(av[1], "-v", 2))
		ch->flag_v = 1;
}

void	stack_is_sort(t_ps *ps)
{
	t_node *node;

	node = ps->stack_a.top;
	while (node && node->next != NULL)
	{
		if (node->data > node->next->data)
			sys_err("KO\n");
		node = node->next;
	}
	if (ps->stack_b.count != 0)
		sys_err("KO\n");
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
