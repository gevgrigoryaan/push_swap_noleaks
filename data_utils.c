/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gegrigor <gevgrigoryaan@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 13:08:55 by gegrigor          #+#    #+#             */
/*   Updated: 2026/03/10 13:15:08 by gegrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
