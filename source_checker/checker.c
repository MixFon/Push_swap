/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 11:25:50 by widraugr          #+#    #+#             */
/*   Updated: 2020/02/03 09:32:55 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	add_node_op(t_ch *ch, char *line)
{
	t_op	*tmp;
	t_op	*it;

	if (ch->op == NULL)
	{
		ch->op = create_node_op(line);
		ch->iter = ch->op;
		return ;
	}
	it = ch->op;
	while (it->next)
		it = it->next;
	tmp = create_node_op(line);
	it->next = tmp;
}

void	read_input(t_ch *ch)
{
	char *line;

	line = NULL;
	while (get_next_line(0, &line) != 0)
	{
		check(line);
		add_node_op(ch, line);
		ft_strdel(&line);
	}
	if (ch->op == NULL)
	{
		stack_is_sort(&ch->ps);
		exit(0);
	}
	ft_strdel(&line);
}

void	print_op(t_ch *ch)
{
	t_op *op;

	op = ch->op;
	while (op)
	{
		ft_putendl(op->op);
		op = op->next;
	}
}

int		press_key(int key)
{
	if (key == 53)
		sys_err("Normal exit.\n");
	return (0);
}

int		main(int ac, char **av)
{
	t_ch	ch;

	if (ac < 2)
		sys_err("To few arguments.\n");
	check_flag_v(&ch, ac, av);
	init(&ch.ps);
	if (ch.flag_v)
		processing_args(&ch.ps, ac - 1, av + 1);
	else
		processing_args(&ch.ps, ac, av);
	read_input(&ch);
	if (ch.flag_v)
	{
		init_ch(&ch);
		mlx_key_hook(ch.window, press_key, &ch);
		mlx_loop_hook(ch.mlx, work_operators, &ch);
		mlx_loop(ch.mlx);
	}
	else
		while (1)
			work_operators(&ch);
	return (0);
}
