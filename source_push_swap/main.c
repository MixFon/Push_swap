#include "../include/push_swap.h"

void	init(t_ps *ps)
{
	ps->stack_a.top = NULL;
	ps->stack_a.bott = NULL;
	ps->stack_a.el_to_top = NULL;
	ps->stack_a.min = NULL;
	ps->stack_a.count = 0;
	ps->stack_a.bl_r = 0;
	ps->stack_a.bl_rr = 0;
	ps->stack_b.top = NULL;
	ps->stack_b.bott = NULL;
	ps->stack_b.el_to_top = NULL;
	ps->stack_b.min = NULL;
	ps->stack_b.count = 0;
	ps->stack_b.bl_r = 0;
	ps->stack_b.bl_rr = 0;
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

void	determine_minimal_el(t_ps *ps)
{
	t_node *node;

	node = ps->stack_a.top;
	ps->stack_a.min = node;
	while (node)
	{
		if (ps->stack_a.min->data > node->data)
			ps->stack_a.min = node;
		node = node->next;
	}
	ft_printf("min->data = [%d] min->number = [%d]\n", ps->stack_a.min->data,
			ps->stack_a.min->number);
}

int		is_cycle_sort(t_ps *ps)
{
	t_node	*node;

	determine_minimal_el(ps);
	node = ps->stack_a.top;
	while (node && node->next)
	{
		ft_printf("node->data = [%d]\n", node->data);
		if (node->data > node->next->data && node->next != ps->stack_a.min)
			return (0);
		node = node->next;
	}
	if (ps->stack_a.top == ps->stack_a.min)
		return (1);
	if (ps->stack_a.top->data < ps->stack_a.bott->data)
		return (0);
	return (1);
}

int		count_steps_to_top(t_stack *stack, int data)
{
	t_node *node;
	int		res;

	res = 0;
	node = stack->top;
	while (node)
	{
		if (node->data == data)
		{
			if (node->number <= stack->count / 2) 
			{
				res = node->number;
				stack->bl_r = 1;
				stack->bl_rr = 0;
			}
			else
			{
				res = (stack->count - node->number);
				stack->bl_r = 0;
				stack->bl_rr = 1;
			}
			stack->el_to_top = node;
			return (res);
		}
		node = node->next;
	}
	return (0);
}

int		count_steps(t_ps *ps, int data)
{
	int		steps;
	t_node	*node;

	node = ps->stack_a.top;
	steps = count_steps_to_top(&ps->stack_b, data);
	if (data < ps->stack_a.top->data && data > ps->stack_a.bott->data)
	{
		ft_putendl("aa");
		steps += count_steps_to_top(&ps->stack_a, node->data);
		return (steps + 1);
	}
	while (node->next)
	{
		if (node->data < data &&
				(node->next->data > data || node->next == ps->stack_a.min))
		{
			ft_putendl("dd");
			steps += count_steps_to_top(&ps->stack_a, node->next->data);
			break;
		}
		node = node->next;
	}
	if (node->next == NULL)
		count_steps_to_top(&ps->stack_a, ps->stack_a.min->data);
	ft_putendl("cc");
	//count_steps_to_top(&ps->stack_a, ps->stack_a.top->data);
	return (steps + 1);
}

t_node	*search_min_el(t_ps *ps)
{
	t_node	*node;
	t_node	*min_el;
	int		steps;
	int		tmp;

	node = ps->stack_b.top;
	min_el = node;
	steps = ps->stack_b.count;
	while (node)
	{
		tmp = count_steps(ps, node->data);
		if (steps > tmp)
		{
			steps = tmp;
			min_el = node;
		}
		ft_printf("data = [%d] steps = [%d]\n", node->data,
				tmp);
		node = node->next;
	}
	ft_printf("min data = [%d] steps = [%d]\n", min_el->data,
			count_steps(ps, min_el->data));
	ft_printf("stack_a.min = [%d]\n", ps->stack_a.min->data);
	ft_printf("el_to_top A  = [%d]\n", ps->stack_a.el_to_top->data);
	ft_printf("el_to_top B  = [%d]\n", ps->stack_b.el_to_top->data);
	return (min_el);
}

void	move_min_el(t_ps *ps, t_node *node)
{
	while (ps->stack_a.bl_r || ps->stack_a.bl_rr ||
			ps->stack_b.bl_r || ps->stack_b.bl_rr)
	{
		if (ps->stack_a.top == ps->stack_a.el_to_top)
		{
			ps->stack_a.bl_r = 0;
			ps->stack_a.bl_rr = 0;
		}
		if (ps->stack_b.top == ps->stack_b.el_to_top)
		{
			ps->stack_b.bl_r = 0;
			ps->stack_b.bl_rr = 0;
		}
		if (ps->stack_a.bl_r && ps->stack_b.bl_r)
			op_rr(ps);
		else if (ps->stack_a.bl_rr && ps->stack_b.bl_rr)
			op_rrr(ps);
		else if (ps->stack_a.bl_rr)
			op_rra(ps);
		else if (ps->stack_a.bl_r)
			op_ra(ps);
		else if (ps->stack_b.bl_r)
			op_rb(ps);
		else if (ps->stack_b.bl_rr)
			op_rrb(ps);
	}
}

void	empty_stack_b(t_ps *ps)
{
	t_node *min_el;

	while (ps->stack_b.count > 0)
	{
		determine_minimal_el(ps);
		min_el = search_min_el(ps);
		move_min_el(ps, min_el);
		op_pa(ps);
		recount_number_stack(ps->stack_a.top);
		recount_number_stack(ps->stack_b.top);
		print_node(&ps->stack_a, &ps->stack_b);
	}
}
void	final_sort(t_ps *ps)
{
	if (ps->stack_a.min->data <= ps->stack_a.count / 2)
		while (ps->stack_a.top != ps->stack_a.min)
			op_ra(ps);
	else 
		while (ps->stack_a.top != ps->stack_a.min)
			op_rra(ps);
}

void	algoritm(t_ps *ps)
{
	int num_item;

	print_node(&ps->stack_a, &ps->stack_b);
	ft_printf("is cycle = [%d]\n", is_cycle_sort(ps));
	while (!is_cycle_sort(ps) && ps->stack_a.count > 3)
	{
		op_pb(ps);
		recount_number_stack(ps->stack_a.top);
		recount_number_stack(ps->stack_b.top);
	}
	print_node(&ps->stack_a, &ps->stack_b);
	if (!is_cycle_sort(ps) && ps->stack_b.count == 0)
		sort_three_elemts_bott(ps, &ps->stack_a);
	print_node(&ps->stack_a, &ps->stack_b);
	empty_stack_b(ps);
	final_sort(ps);
	print_node(&ps->stack_a, &ps->stack_b);
	//ft_printf("is cycle = [%d]\n", is_cycle_sort(ps));
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
