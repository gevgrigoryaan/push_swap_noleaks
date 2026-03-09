/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gegrigor <gegrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 16:11:26 by gegrigor          #+#    #+#             */
/*   Updated: 2026/03/09 17:34:25 by gegrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

t_count	*init_count(void)
{
	t_count	*count;

	count = malloc(sizeof(t_count));
	if (!count)
		return (NULL);
	count->op_pa = 0;
	count->op_pb = 0;
	count->op_sa = 0;
	count->op_sb = 0;
	count->op_ss = 0;
	count->op_ra = 0;
	count->op_rb = 0;
	count->op_rr = 0;
	count->op_rra = 0;
	count->op_rrb = 0;
	count->op_rrr = 0;
	return (count);
}

static float	compute_disorder(t_stack **a)
{
	int		mistakes;
	int		total_pairs;
	t_stack	*i;
	t_stack	*j;

	mistakes = 0;
	total_pairs = 0;
	i = (*a);
	while (i)
	{
		j = i->next;
		while (j)
		{
			total_pairs += 1;
			if (i->value > j->value)
				mistakes += 1;
			j = j->next;
		}
		i = i->next;
	}
	return ((float)mistakes / total_pairs);
}

void	adaptive_mode(t_stack **a, t_count *count, float disorder, t_mode *mode)
{
	int		n;
	t_stack	*b_stack;

	b_stack = NULL;
	n = stack_size(*a);
	if (n == 2)
		sort_two(a, count);
	else if (n == 3)
		sort_three(a, count);
	else if (n == 5)
		sort_five(a, &b_stack, count);
	else
	{
		if (disorder < 0.2)
			mode->sorter = SIMPLE;
		else if (disorder >= 0.2 && disorder < 0.5)
			mode->sorter = MEDIUM;
		else if (disorder >= 0.5)
			mode->sorter = COMPLEX;
	}
}

void	sorter(t_stack **a, t_stack **b, int n, t_data *data)
{
	float	disorder;
	int		real_mode;

	if (!*a)
		exit(0);
	data->count = init_count();
	disorder = compute_disorder(a);
	real_mode = data->mode->sorter;
	if (!is_sorted(*a))
	{
		if (data->mode->sorter == ADAPTIVE)
			adaptive_mode(a, data->count, disorder, data->mode);
		if (data->mode->sorter == SIMPLE)
			bubble_sort(a, data->count);
		if (data->mode->sorter == MEDIUM)
			chunk_sort(a, b, n, data->count);
		if (data->mode->sorter == COMPLEX)
			radix_sort(a, b, n, data->count);
	}
	if (data->mode->bench == ON)
		bench_mode(disorder, real_mode, data->count, data->mode);
}
