/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rra_rrb_rrr_sa_sb.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 10:35:04 by widraugr          #+#    #+#             */
/*   Updated: 2020/01/30 11:46:32 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

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
