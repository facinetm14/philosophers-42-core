/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 03:01:23 by fakouyat          #+#    #+#             */
/*   Updated: 2022/09/02 03:01:23 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_prog		var_prog;
	pthread_t	sup_visor[MAX_PHILO];

	ft_check_input(argc, argv, &var_prog);
	var_prog.start = get_time_in_ms();
	lunch_philos_runtine(sup_visor, &var_prog);
	ft_destroy_mutexes(&var_prog);
	return (0);
}
