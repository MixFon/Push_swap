#include "../include/push_swap.h"

void	init_ch(t_ch *ch)
{
	ch->op = NULL;
	ch->mlx = mlx_init();
	ch->window = mlx_new_window(ch->mlx, WIDTH, HEIGHT, "Push swap");	
}

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

t_coor	ft_draw_line_source(t_coor *delta,
		t_coor *sign, t_coor point1, t_coor point2)
{
	(*delta).x = ABS((point2.x - point1.x));
	(*delta).y = ABS((point2.y - point1.y));
	(*sign).x = (point1.x < point2.x) ? 1 : -1;
	(*sign).y = (point1.y < point2.y) ? 1 : -1;
	return (point1);
}

void	ft_draw_line(t_ch *ch, t_coor point1, t_coor point2)
{
	t_coor	delta;
	t_coor	sign;
	t_coor	point;
	int		error;
	int		error2;

	point = ft_draw_line_source(&delta, &sign, point1, point2);
	error = delta.x - delta.y;
	//put_pixel_adr(fdf, point2);
	mlx_pixel_put(ch->mlx, ch->window, point2.x, point2.y, 0xff00);
	while (point.x != point2.x || point.y != point2.y)
	{
		//put_pixel_adr(fdf, point);
		mlx_pixel_put(ch->mlx, ch->window, point.x, point.y, 0xff00);
		error2 = error * 2;
		if (error2 > -delta.y)
		{
			error -= delta.y;
			point.x += sign.x;
		}
		if (error2 < delta.x)
		{
			error += delta.x;
			point.y += sign.y;
		}
		//point.color = 0x//get_color(point, point1, point2, delta);
	}
}

void	mlx_put_stacks(t_ch *ch)
{
	t_coor point1;
	t_coor point2;
	t_node *node;

	node = ch->ps.stack_a.top;
	point1.x = 50;
	point1.y = 100;
	point2.y = 100;
	while (node)
	{
		point2.x = node->data + 50;
		ft_draw_line(ch, point1, point2);
		node = node->next;
		point1.y += 3;
		point2.y += 3;
	}
	node = ch->ps.stack_b.top;
	point2.x = HALFWID;
	point1.y = 100;
	point2.y = 100;
	while (node)
	{
		point1.x = node->data + HALFWID;
		ft_draw_line(ch, point2, point1);
		node = node->next;
		point1.y += 3;
		point2.y += 3;
	}
}

void	work_perations(t_ch *ch, t_ps *ps, char *line)
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
		if (node->data > node->next->data)
		{
			print_node(&ps->stack_a, &ps->stack_b);
			ft_putendl("KO!");
			return ;
		}
		node = node->next;
	}
	print_node(&ps->stack_a, &ps->stack_b);
	ft_putendl("OK");
}

int		work_operators(t_ch *ch)
{
	mlx_clear_window(ch->mlx, ch->window);
	//usleep(200000);
	work_perations(ch, &ch->ps, ch->iter->op);
	mlx_put_stacks(ch);
	ch->iter = ch->iter->next;
	if (ch->iter == NULL)
	{
		stack_is_sort(&ch->ps);
		mlx_put_stacks(ch);
		sleep(3);
		sys_err("iter NULL\n");
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

void	add_node_op(t_ch *ch, char *line)
{
	t_op *tmp;
	t_op *it;

	if (ch->op == NULL)
	{
		ch->op = create_node_op(line);
		ch->iter = ch->op;
		return ;
	}
	it = ch->op;
	while(it->next)
		it = it->next;
	tmp = create_node_op(line);
	it->next = tmp;
}


void	read_input(t_ch *ch)
{
	char *line;

	while (get_next_line(0, &line))
	{
		check(line);
		add_node_op(ch, line);
		//work_perations(&ch->ps, line);
		//ft_printf("<%s\n", line);
		//mlx_string_put(ch->mlx, ch->window, i, i, 0xff00, line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	//stack_is_sort(&ch->ps);
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
	init(&ch.ps);
	init_ch(&ch);
	processing_args(&ch.ps, ac, av);
	read_input(&ch);
	//print_op(&ch);
	mlx_key_hook(ch.window, press_key, &ch);
	mlx_loop_hook(ch.mlx, work_operators, &ch);
	//mlx_key_hook(ch.window, work_operators, &ch);
	mlx_loop(ch.mlx);
	return (0);
}
