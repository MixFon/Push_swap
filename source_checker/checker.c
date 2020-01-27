#include "../include/push_swap.h"

void	check(char *line)
{
	if (ft_strlen(line) > 4 || ft_strlen(line) < 2)
	{
		ft_printf("Operation \"%s\" is not valid.\n", line);
		exit(0);
	}
	if (ft_strstr(STROP, line) == NULL)	
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
	else if (!ft_strcmp(line, "rrr"))
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
}

void	stack_is_sort(t_ps *ps)
{
	t_node *node;

	node = ps->stack_a.top;
	while (node && node->next != ps->stack_a.bott)
	{
		//ft_printf("node->data = [%d]\n", node->data);
		if (node->data > node->next->data)
		{
			print_node(&ps->stack_a, &ps->stack_b);
			sys_err("KO!\n");
		}
		node = node->next;
	}
	print_node(&ps->stack_a, &ps->stack_b);
	ft_putendl("OK");
}

void	checke_operators(t_ps *ps)
{
	char *line;

	while (get_next_line(0, &line))
	{
		check(line);
		work_perations(ps, line);
		ft_printf("<%s\n", line);
		//print_node(&ps->stack_a, &ps->stack_b);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	stack_is_sort(ps);
}

int		main(int ac, char **av)
{
	t_ps	ps;

	if (ac < 2)
		sys_err("To few arguments.\n");
	init(&ps);
	processing_args(&ps, ac, av);
	bable_sort(&ps);
	checke_operators(&ps);
	return (0);
}
