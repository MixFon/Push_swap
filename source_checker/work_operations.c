/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 11:32:48 by widraugr          #+#    #+#             */
/*   Updated: 2020/01/30 13:15:49 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	clear_image(t_ch *fdf)
{
	char	*temp;
	int		i;

	temp = fdf->data_adr;
	i = -1;
	while (++i < WIDTH * 4 * HEIGHT)
		temp[i] = 0;
}

void	put_stack(t_ch *ch, t_stack *stack, int start_x)
{
	t_coor point1;
	t_coor point2;
	t_node *node;

	node = stack->top;
	point1.x = start_x;
	point1.y = STARTY;
	point2.y = STARTY;
	while (node)
	{
		point2.x = node->data + start_x;
		ft_draw_line(ch, point1, point2, 0xff00);
		node = node->next;
		point1.y += 2;
		point2.y += 2;
	}
}

void	mlx_put_stacks(t_ch *ch)
{
	t_coor point1;
	t_coor point2;

	point1.x = 0;
	point1.y = STARTY;
	point2.x = WIDTH;
	point2.y = STARTY;
	put_stack(ch, &ch->ps.stack_a, 100);
	put_stack(ch, &ch->ps.stack_b, HALFWID);
	ft_draw_line(ch, point1, point2, 0xffff);
	mlx_put_image_to_window(ch->mlx, ch->window, ch->img_ptr, 0, 0);
	mlx_string_put(ch->mlx, ch->window, 130, STARTY - 30, 0xffff, "Stack A");
	mlx_string_put(ch->mlx, ch->window,
			HALFWID + 30, STARTY - 30, 0xffff, "Stack B");
}

void	work_perations_next(t_ps *ps, char *line)
{
	if (!ft_strcmp(line, "rrr"))
	{
		op_reverse_rotate(&ps->stack_a);
		op_reverse_rotate(&ps->stack_b);
	}
	else if (!ft_strcmp(line, "sa"))
		op_swap(&ps->stack_a);
	else if (!ft_strcmp(line, "sb"))
		op_swap(&ps->stack_b);
	else if (!ft_strcmp(line, "ss"))
	{
		op_swap(&ps->stack_a);
		op_swap(&ps->stack_b);
	}
	else if (line != NULL)
	{
		ft_printf("Operation \"%s\" is not valid.\n", line);
		exit(0);
	}
}

void	work_perations(t_ps *ps, char *line)
{
	if (!ft_strcmp(line, "pa"))
		op_push(&ps->stack_b, &ps->stack_a);
	else if (!ft_strcmp(line, "pb"))
		op_push(&ps->stack_a, &ps->stack_b);
	else if (!ft_strcmp(line, "ra"))
		op_rotate(&ps->stack_a);
	else if (!ft_strcmp(line, "rb"))
		op_rotate(&ps->stack_b);
	else if (!ft_strcmp(line, "rr"))
	{
		op_rotate(&ps->stack_a);
		op_rotate(&ps->stack_b);
	}
	else if (!ft_strcmp(line, "rra"))
		op_reverse_rotate(&ps->stack_a);
	else if (!ft_strcmp(line, "rrb"))
		op_reverse_rotate(&ps->stack_b);
	else
		work_perations_next(ps, line);
}
