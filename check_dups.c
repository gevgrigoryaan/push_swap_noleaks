/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dups.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gegrigor <gegrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 11:09:38 by gegrigor          #+#    #+#             */
/*   Updated: 2026/03/09 17:28:39 by gegrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	check_dups(t_stack *a, t_data *data)
{
	t_stack	*tmp;
	int		i;
	int		j;
	int		n;

	n = stack_size(a);
	i = 0;
	while (i < n)
	{
		tmp = a->next;
		j = i + 1;
		while (j < n)
		{
			if (a->value == tmp->value)
				exit_error(data);
			j++;
			tmp = tmp->next;
		}
		i++;
		a = a->next;
	}
}
