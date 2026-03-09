/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gegrigor <gegrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 19:14:39 by gegrigor          #+#    #+#             */
/*   Updated: 2026/03/09 18:16:08 by gegrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <limits.h>

void	free_data(t_data *data)
{
	int	i;

	free_stack(data->a);
	free_stack(data->b);
	free(data->mode);
	free(data->count);
	if (data->args)
	{
		i = 0;
		while (data->args[i])
		{
			free(data->args[i]);
			i++;
		}
		free(data->args);
	}
	free(data);
}

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->a = NULL;
	data->b = NULL;
	data->mode = NULL;
	data->count = NULL;
	data->args = NULL;
	return (data);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	int		i;

	i = 0;
	if (argc < 2)
		return (0);
	data = init_data();
	data->args = get_args(argc, argv);
	data->mode = init_flags();
	i += flags(data->args, data->mode, data);
	if (argc - i == 1 || !is_valid(data->args + i, argc - i - 1))
		exit_error(data);
	data->a = fill_stack_values(data->args + i, data);
	data->b = NULL;
	sorter(&(data->a), &(data->b), stack_size(data->a), data);
	free_data(data);
	return (0);
}
