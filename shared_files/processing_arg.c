/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 11:50:38 by widraugr          #+#    #+#             */
/*   Updated: 2020/01/30 11:52:36 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int		check_number(char *arg)
{
	long long	data;
	int			i;
	int			bl;

	data = 0;
	i = 0;
	bl = (*arg == '-' ? -1 : 1);
	if (*arg == '-' || *arg == '+')
		arg++;
	while (*arg != '\0')
	{
		data = data * 10 + (*arg - '0');
		arg++;
		i++;
	}
	data *= bl;
	if (i > 10 || data > INT_MAX || data < INT_MIN || i == 0)
	{
		ft_printf("Arguments %ld is not an integer type.\n", data);
		exit(0);
	}
	return ((int)data);
}

void	infill_stack(t_ps *ps, char **av)
{
	int num;

	while (*av != '\0')
	{
		check_arg(*av);
		num = check_number(*av);
		add_node(ps, num);
		av++;
	}
}

void	dell_arr(char ***arr)
{
	int i;

	i = -1;
	if (arr == NULL)
		return ;
	if (*arr == NULL)
		return ;
	if (**arr == NULL)
		return ;
	while (arr[0][++i] != NULL)
		ft_strdel(&arr[0][i]);
	free(*arr);
}

void	delete_stack(t_stack *stack)
{
	t_node *node;

	while (stack->top)
	{
		node = stack->top;
		stack->top = stack->top->next;
		free(node);
	}
}

void	processing_args(t_ps *ps, int ac, char **av)
{
	char	**args;
	int		count_args;

	if (ac == 1)
		exit(0);
	if (ac > 2)
		infill_stack(ps, av + 1);
	else
	{
		args = ft_strsplit(av[1], ' ');
		count_args = ft_numwr(av[1], ' ');
		infill_stack(ps, args);
		dell_arr(&args);
	}
}
