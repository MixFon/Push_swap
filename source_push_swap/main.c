#include "../include/push_swap.h"

void	init(t_ps *ps)
{
	ps->stack_a.top = NULL;
	ps->stack_a.bott = NULL;
	ps->stack_a.count = 0;
	ps->stack_a.bl_ss = 0;
	ps->stack_a.bl_rr = 0;
	ps->stack_b.top = NULL;
	ps->stack_b.bott = NULL;
	ps->stack_b.count = 0;
	ps->stack_b.bl_ss = 0;
	ps->stack_b.bl_rr = 0;
	ps->only_top = 0;
	ps->only_top = 0;
}

void	ft_swap(int a, int b)
{
	int tmp;
	int X[10];
	int Y[10];
	int i;

	if (X[i] < X[i + 1])
	{
		tmp = X[i];
		X[i] = X[i + 1];
		X[i + 1] = tmp;
		tmp = Y[i];
		Y[i] = Y[i + 1];
		Y[i + 1] = tmp;
	}
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
	//print_sort_arr(ps);
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

void	op_pa(t_ps *ps)
{
	op_push(&ps->stack_b, &ps->stack_a);
	ft_putendl("pa");
}

void	op_pb(t_ps *ps)
{
	op_push(&ps->stack_a, &ps->stack_b);
	ft_putendl("pb");
}

void	op_ra(t_ps *ps)
{
	op_rotate(&ps->stack_a);
	ft_putendl("ra");
}

void	op_rb(t_ps *ps)
{
	op_rotate(&ps->stack_b);
	ft_putendl("rb");
}

void	op_rr(t_ps *ps)
{
	op_rotate(&ps->stack_a);
	op_rotate(&ps->stack_b);
	ft_putendl("rr");
}

void	op_rra(t_ps *ps)
{
	op_reverse_rotate(&ps->stack_a);
	ft_putendl("rra");
}

void	op_rrb(t_ps *ps)
{
	op_reverse_rotate(&ps->stack_b);
	ft_putendl("rb");
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

void	op_ss(t_ps *ps)
{
	op_swap(&ps->stack_a);
	op_swap(&ps->stack_b);
	ft_putendl("ss");
}

void	operations(t_ps *ps)
{
	print_node(&ps->stack_a, &ps->stack_b);
	op_reverse_rotate(&ps->stack_a);
	print_node(&ps->stack_a, &ps->stack_b);
	op_reverse_rotate(&ps->stack_a);
	print_node(&ps->stack_a, &ps->stack_b);
	op_reverse_rotate(&ps->stack_a);
	print_node(&ps->stack_a, &ps->stack_b);
	op_reverse_rotate(&ps->stack_a);
	print_node(&ps->stack_a, &ps->stack_b);
}

void	to_top_with_rr(t_ps *ps)
{
	if (ps->stack_b.bl_rr == 1)
	{
		op_rr(ps);
		ps->stack_b.bl_rr = 0;
	}
	else
		op_ra(ps);
}

void	move_all_to_stack_a(t_ps *ps)
{
	while (ps->stack_b.count > 0)
		op_pa(ps);
}

void	sort_three_elemts_bott(t_ps *ps, t_stack *stack)
{
	if (stack->top->data < stack->top->next->data &&
			stack->top->next->data < stack->bott->data)
	{
		ft_putendl("11");
		move_all_to_stack_a(ps);
		return ;
	}
	else if (stack->bott->data > stack->top->data &&
			stack->bott->data < stack->top->next->data)
	{
		ft_putendl("22");
		op_rra(ps);
		op_sa(ps);
	}
	else if (stack->top->data > stack->top->next->data &&
			stack->top->data < stack->bott->data)
	{
		ft_putendl("33");
		op_sa(ps);
	}
	else if (stack->top->data < stack->top->next->data &&
			stack->top->data > stack->bott->data)
	{
		ft_putendl("44");
		op_rra(ps);
	}
	else if (stack->bott->data > stack->top->next->data &&
			stack->bott->data < stack->top->data)
	{
		ft_putendl("55");
		to_top_with_rr(ps);
	}
	else if (stack->top->next->data < stack->top->data &&
			stack->top->next->data > stack->bott->data)
	{
		ft_putendl("66");
		op_sa(ps);
		op_rra(ps);
	}
	move_all_to_stack_a(ps);
}

void	sort_three_elemts_top(t_ps *ps, t_stack *stack)
{
	if (stack->bott->data > stack->top->next->data &&
			stack->bott->data < stack->top->data)
	{
		ft_putendl("111");
		move_all_to_stack_a(ps);
		op_rra(ps);
		op_rra(ps);
		return ;
	}
	else if (stack->top->next->data < stack->top->data &&
			stack->top->next->data > stack->bott->data)
	{
		ft_putendl("222");
		op_rra(ps);
		op_sa(ps);
	}
	else if (stack->top->data < stack->bott->data &&
			stack->top->next->data > stack->bott->data)
	{
		ft_putendl("333");
		op_sa(ps);
	}
	else if (stack->top->data < stack->top->next->data &&
			stack->top->next->data < stack->bott->data)
	{
		ft_putendl("444");
		op_rra(ps);
	}
	else if (stack->top->data > stack->top->next->data &&
			stack->top->data < stack->bott->data)
	{
		ft_putendl("555");
		to_top_with_rr(ps);
		op_sa(ps);
	}
	else if (stack->top->data < stack->top->next->data &&
			stack->top->data > stack->bott->data)
	{
		ft_putendl("666");
		to_top_with_rr(ps);
	}
	move_all_to_stack_a(ps);
	op_rra(ps);
	op_rra(ps);
}

void	sort_three_elemts(t_ps *ps, t_stack *stack)
{
	if (stack->top->data < stack->top->next->data &&
			stack->top->data > stack->bott->data)
	{
		ft_putendl("1");
		move_all_to_stack_a(ps);
		op_rra(ps);
		return ;
	}
	else if (stack->top->data > stack->top->next->data &&
			stack->top->data < stack->bott->data)
	{
		ft_putendl("2");
		op_rra(ps);
		op_sa(ps);
	}
	else if (stack->top->data > stack->top->next->data &&
			stack->top->next->data > stack->bott->data)
	{
		ft_putendl("3");
		op_sa(ps);
	}
	else if (stack->bott->data > stack->top->next->data &&
			stack->bott->data < stack->top->data)
	{
		ft_putendl("4");
		op_rra(ps);
	}
	else if (stack->bott->data < stack->top->next->data &&
			stack->bott->data > stack->top->data)
	{
		ft_putendl("5");
		to_top_with_rr(ps);
		op_sa(ps);
	}
	else if (stack->top->data < stack->top->next->data &&
			stack->bott->data > stack->top->next->data)
	{
		ft_putendl("6");
		to_top_with_rr(ps);
	}
	move_all_to_stack_a(ps);
	op_rra(ps);
}

void	sort_two_elemts(t_ps *ps, t_stack *stack)
{
	ft_putendl("!!!!");
	if (stack->top->data == ps->sotr_arr[ps->count_arr - 1] && 
			stack->top->next->data == ps->sotr_arr[0])
	{
		ft_putendl("11111");
		move_all_to_stack_a(ps);
		op_rra(ps);
	}
	else if (stack->top->data == ps->sotr_arr[0] && 
			stack->top->next->data == ps->sotr_arr[ps->count_arr - 1])
	{
		ft_putendl("22222");
		op_sa(ps);
		move_all_to_stack_a(ps);
		op_rra(ps);
	}
	else if (stack->top->data == ps->sotr_arr[1] && 
			stack->top->next->data == ps->sotr_arr[0])
	{
		ft_putendl("33333");
		op_sa(ps);
		move_all_to_stack_a(ps);
		op_rra(ps);
		op_rra(ps);
	}
	else if (stack->top->data == ps->sotr_arr[0] && 
			stack->top->next->data == ps->sotr_arr[1])
	{
		ft_putendl("44444");
		move_all_to_stack_a(ps);
		op_rra(ps);
		op_rra(ps);
	}
	else if (stack->top->data == ps->sotr_arr[ps->count_arr - 1] && 
			stack->top->next->data == ps->sotr_arr[ps->count_arr - 2])
	{
		ft_putendl("55555");
		op_sa(ps);
		move_all_to_stack_a(ps);
	}
	else if (stack->top->data == ps->sotr_arr[ps->count_arr - 2] && 
			stack->top->next->data == ps->sotr_arr[ps->count_arr - 1])
	{
		ft_putendl("66666");
		move_all_to_stack_a(ps);
	}
}

void	algoritm(t_ps *ps)
{
	int num_item;

	print_node(&ps->stack_a, &ps->stack_b);
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
	//operations(&ps);
	algoritm(&ps);
	return (0);
}
