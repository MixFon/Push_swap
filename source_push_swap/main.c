#include "../include/push_swap.h"

void	init(t_ps *ps)
{
	ps->stack_a.top = NULL;
	ps->stack_a.bott = NULL;
	ps->stack_a.count = 0;
	ps->stack_b.top = NULL;
	ps->stack_b.bott = NULL;
	ps->stack_b.count = 0;
	ps->mid[0].item = 0;
	ps->mid[1].item = 0;
	ps->mid[2].item = 0;
	ps->mid[0].num_item_sort = 0;
	ps->mid[1].num_item_sort = 0;
	ps->mid[2].num_item_sort = 0;
}

void		check_arg(char *arg)
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
		i++; }
	data *= bl;
	if (i > 10 || data > INT_MAX || data < INT_MIN || i == 0)
	{
		ft_printf("Arguments %ld is not an integer type.\n", data);
		exit(0);
	}
	return ((int)data);
}

t_node	*create_node(int data, size_t *count)
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

void	search_dublicate(t_node *node, int data)
{
	while (node)
	{
		if (node->data == data)
			sys_err("Found dublicate.\n");
		node = node->next;
	}
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
			ft_printf("{%d}\n",node_b->data);
		else
			ft_printf("{%c}\n", ' ');
		if (node_a)
			node_a = node_a->next;
		if (node_b)
			node_b = node_b->next;
	}
}

void	print_sort_arr(t_ps *ps)
{
	int *arr;
	int i;

	i = -1;
	arr = ps->sotr_arr;
	ft_printf("Sort arr [%d]\n", ps->count_arr);
	while (++i < ps->count_arr)
		ft_printf("%d\n", arr[i]);
}

void	infill_stack(t_ps *ps, int ac, char **av)
{
	int num;
	int i;

	i = -1;
	ps->count_arr = ac - 1;
	if (!(ps->sotr_arr = (int*)malloc(sizeof(int) * (ac - 1))))
		sys_err("Error malloc.\n");
	while (*av != '\0')
	{
		check_arg(*av);
		num = check_number(*av);
		add_node(ps, num);
		ps->sotr_arr[++i] = num;
		av++;
	}
	print_sort_arr(ps);
	print_node(&ps->stack_a, &ps->stack_b);
}

void	recount_number_stack(t_node *node)
{
	size_t	number;

	number = -1;
	while (node)
	{
		node->number = ++number;
		node = node->next;
	}
}

void	op_swap(t_stack *stack)
{
	t_node *node;

	ft_putendl("swap");
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

	ft_putendl("rotate");
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

	ft_putendl("reverse rotate");
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

	ft_putendl("push");
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

void	operations(t_ps *ps)
{
	op_swap(&ps->stack_a);
	print_node(&ps->stack_a, &ps->stack_b);
	op_rotate(&ps->stack_a);
	print_node(&ps->stack_a, &ps->stack_b);
	op_reverse_rotate(&ps->stack_a);
	print_node(&ps->stack_a, &ps->stack_b);
	op_push(&ps->stack_a, &ps->stack_b);
	print_node(&ps->stack_a, &ps->stack_b);
	op_push(&ps->stack_a, &ps->stack_b);
	print_node(&ps->stack_a, &ps->stack_b);
	op_push(&ps->stack_a, &ps->stack_b);
	print_node(&ps->stack_a, &ps->stack_b);
	op_push(&ps->stack_b, &ps->stack_a);
	print_node(&ps->stack_a, &ps->stack_b);
	op_push(&ps->stack_b, &ps->stack_a);
	print_node(&ps->stack_a, &ps->stack_b);
}

int		count_steps_to_top(t_ps *ps, int i)
{
	t_node *node;
	int		res;

	res = 0;
	node = ps->stack_a.top;
	while (node)
	{
		if (node->data == ps->mid[i].item)
		{
			if (node->number <= ps->stack_a.count / 2) 
				res = node->number;
			else
				res = (ps->stack_a.count - node->number) * (-1);
			return (res);
		}
		node = node->next;
	}
	return (-1);
}

int		count_steps(t_ps *ps, int i)
{
	int to_top;

	to_top = count_steps_to_top(ps, i);
	if (to_top < 0)
		to_top = to_top * (-1);
	if (i == 0 || ps->stack_b.count == 0)
		return (to_top + 1);
	return (to_top + 2);
}

int		item_to_move(t_ps *ps)
{
	int item;
	int steps;
	int	tmp;
	int i;

	i = 0;
	steps = count_steps(ps, i);
	item = i;
	ft_printf("steps mid[%d] [%d] = {%d}\n", i, ps->mid[i], steps);
	while (++i < 3)
	{
		tmp = count_steps(ps, i);
		ft_printf("steps mid[%d] [%d] = {%d}\n", i, ps->mid[i], tmp);
		if (tmp < steps)
		{
			steps = tmp;
			item = i;
		}
	}
	ft_printf("min steps mid[%d] [%d] = {%d}\n", item, ps->mid[item], steps);
	return (item);
}

void	move_item_to_top(t_ps *ps, int item)
{
	int steps_to_top;

	ft_printf("item {%d}\n", item);
	steps_to_top = count_steps_to_top(ps, item);
	ft_printf("steps_to_top {%d}\n", steps_to_top);
	if (steps_to_top >= 0)
		while (ps->stack_a.top->data != ps->mid[item].item)
			op_rotate(&ps->stack_a);
	else
		while (ps->stack_a.top->data != ps->mid[item].item)
			op_reverse_rotate(&ps->stack_a);
//	print_node(&ps->stack_a, &ps->stack_b);
}

void	move_item(t_ps *ps, int num_item)
{
	move_item_to_top(ps, num_item);
	if (num_item == 0)
	{
		op_push(&ps->stack_a, &ps->stack_b);
		op_rotate(&ps->stack_b);
		//print_node(&ps->stack_a, &ps->stack_b);
	}
	else if (num_item == 1)
		op_push(&ps->stack_a, &ps->stack_b);
	else if (num_item == 2)
	{
		op_push(&ps->stack_a, &ps->stack_b);
		move_item_to_top(ps, 1);
		op_push(&ps->stack_a, &ps->stack_b);
		op_swap(&ps->stack_b);
	}
	recount_number_stack(ps->stack_a.top);
	recount_number_stack(ps->stack_b.top);
	print_node(&ps->stack_a, &ps->stack_b);
}

void	recount_number_item_to_bott(t_ps *ps)
{
	ps->mid[0].num_item_sort++;
	ps->mid[0].item = ps->sotr_arr[ps->mid[0].num_item_sort];
	ps->mid[1].num_item_sort++;
	ps->mid[1].item = ps->sotr_arr[ps->mid[1].num_item_sort];
	ps->mid[2].num_item_sort++;
	ps->mid[2].item = ps->sotr_arr[ps->mid[2].num_item_sort];
}

void	recount_number_item(t_ps *ps, int num_item)
{
	static int	bl = 0;

	if (bl == 1)
		recount_number_item_to_bott(ps);
	else if (num_item == 0)
	{
		ps->mid[num_item].num_item_sort--;
		if (ps->mid[num_item].num_item_sort == -1)
		{
			bl = 1;
			ps->mid[0].num_item_sort = ps->mid[1].num_item_sort - 1;
			recount_number_item_to_bott(ps);
		}
		else
			ps->mid[0].item = ps->sotr_arr[ps->mid[0].num_item_sort];
	}
	else if (num_item == 1)
	{
		ps->mid[1].num_item_sort++;
		ps->mid[1].item = ps->sotr_arr[ps->mid[1].num_item_sort];
		ps->mid[2].num_item_sort++;
		ps->mid[2].item = ps->sotr_arr[ps->mid[2].num_item_sort];
	}
	else if (num_item == 2)
	{
		ps->mid[1].num_item_sort += 2;
		ps->mid[1].item = ps->sotr_arr[ps->mid[1].num_item_sort];
		ps->mid[2].num_item_sort += 2;
		ps->mid[2].item = ps->sotr_arr[ps->mid[2].num_item_sort];
	}
	ft_printf("num_item_sort {%d} = [%d]\n", 0, ps->mid[0].num_item_sort);
	ft_printf("num_item_sort {%d} = [%d]\n", 1, ps->mid[1].num_item_sort);
	ft_printf("num_item_sort {%d} = [%d]\n", 2, ps->mid[2].num_item_sort);
}

void	algoritm(t_ps *ps)
{
	int num_item;

	while (ps->stack_a.count > 3)
	{
		ft_putendl("------------------------------------------------");
		num_item = item_to_move(ps);
		move_item(ps, num_item);
		recount_number_item(ps, num_item);
	}
}

void	bable_sort(t_ps *ps)
{
	int i;
	int j;
	int tmp;

	i = -1;
	while (++i < ps->count_arr)
	{
		j = -1;
		while (++j < ps->count_arr - 1)
		{
			if (ps->sotr_arr[i] < ps->sotr_arr[j])
			{
				tmp = ps->sotr_arr[i];
				ps->sotr_arr[i] = ps->sotr_arr[j];
				ps->sotr_arr[j] = tmp;
			}
		}
	}
	print_sort_arr(ps);
}

void	infill_mid_value(t_ps *ps)
{
	int ind;

	ind = ps->stack_a.count / 2;
	if (ps->stack_a.count < 3)
		sys_err("Fooooo\n");
	ps->mid[0].item = ps->sotr_arr[ind - 1];
	ps->mid[0].num_item_sort = ind - 1;
	ft_printf("mid[0] a = {%d}\n", ps->mid[0]);
	ps->mid[1].item = ps->sotr_arr[ind];
	ps->mid[1].num_item_sort = ind;
	ft_printf("mid[1] c = {%d}\n", ps->mid[1]);
	ps->mid[2].item = ps->sotr_arr[ind + 1];
	ps->mid[2].num_item_sort = ind + 1;
	ft_printf("mid[2] m = {%d}\n", ps->mid[2]);
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

void	processing_args(t_ps *ps, int ac, char **av)
{
	char	**args;
	int		count_args;

	if (ac > 2)
		infill_stack(ps, ac, av + 1);
	else
	{
		args = ft_strsplit(av[1], ' ');
		count_args = ft_numwr(av[1], ' ');
		infill_stack(ps, count_args + 1, args);
		dell_arr(&args);
	}
}

int		main(int ac, char **av)
{
	t_ps	ps;

	if (ac < 2)
		sys_err("To few arguments.\n");
	init(&ps);
	processing_args(&ps, ac, av);
	bable_sort(&ps);
	infill_mid_value(&ps);
	//operations(&ps);
	algoritm(&ps);
	return (0);
}
