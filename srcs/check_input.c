/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:44:52 by fakouyat          #+#    #+#             */
/*   Updated: 2022/09/07 13:44:52 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_check_input(int argc, char **argv, t_prog *var_prog)
{
	if (argc < 5)
	{
		printf("Error : few arguments !\n");
		exit(0);
	}
	if (is_args_int(argc - 1, argv) == 0)
	{
		printf("Error : wrong arguments !\n");
		exit(0);
	}
	ft_parsing(argc, argv, var_prog);
}
