/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gegrigor <gevgrigoryaan@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 17:34:19 by gegrigor          #+#    #+#             */
/*   Updated: 2026/03/10 13:08:05 by gegrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.h"
#include "push_swap.h"
#include <limits.h>

int	is_sorted(t_stack *a)
{
	t_stack	*i;
	t_stack	*j;

	i = a;
	while (i && i->next)
	{
		j = i->next;
		if (i->value > j->value)
			return (0);
		i = i->next;
	}
	return (1);
}

static void	do_operations(t_stack **a, t_stack **b, char *op, t_data *data)
{
	if (!ft_strncmp(op, "sa\n", 3))
		sa_bonus(a);
	else if (!ft_strncmp(op, "sb\n", 3))
		sb_bonus(b);
	else if (!ft_strncmp(op, "ss\n", 3))
		ss_bonus(a, b);
	else if (!ft_strncmp(op, "pa\n", 3))
		pa_bonus(a, b);
	else if (!ft_strncmp(op, "pb\n", 3))
		pb_bonus(a, b);
	else if (!ft_strncmp(op, "ra\n", 3))
		ra_bonus(a);
	else if (!ft_strncmp(op, "rb\n", 3))
		rb_bonus(b);
	else if (!ft_strncmp(op, "rr\n", 3))
		rr_bonus(a, b);
	else if (!ft_strncmp(op, "rra\n", 4))
		rra_bonus(a);
	else if (!ft_strncmp(op, "rrb\n", 4))
		rrb_bonus(b);
	else if (!ft_strncmp(op, "rrr\n", 4))
		rrr_bonus(a, b);
	else
		exit_error(data);
}

static void	read_operations(t_stack **a, t_stack **b, t_data *data)
{
	char	*op;

	op = get_next_line(0);
	while (op)
	{
		do_operations(a, b, op, data);
		free(op);
		op = get_next_line(0);
	}
}

int	main(int argc, char **argv)
{
	t_data *data;
	int		i;

	i = 0;
	if (argc < 2)
		return (0);
	data = init_data();
	data->args = get_args(argc, argv);
	data->mode = init_flags();
	i += flags(data->args, data->mode, data);
	if (!is_valid(data->args + i, argc - i - 1))
		exit_error(data);
	data->a = fill_stack_values((data->args) + i, data);
	data->b = NULL;
	read_operations(&(data->a), &(data->b), data);
	if (is_sorted(data->a) && !(data->b))
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	free_data(data);
	return (0);
}
