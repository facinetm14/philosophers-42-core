/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:04:26 by fakouyat          #+#    #+#             */
/*   Updated: 2022/09/07 15:04:26 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*routine_sup(void *arg)
{
	t_philo	*philo;
	long	curr_time;
	long	diff_time;

	philo = (t_philo *)arg;
	while (1)
	{
		curr_time = get_time_in_ms();
		if (philo->id % 2 == 0)
			usleep(2000);
		pthread_mutex_lock(&philo->status);
		diff_time = curr_time - philo->last_eat;
		pthread_mutex_unlock(&philo->status);
		if (diff_time >= philo->tt_die)
		{
			printf("%10ld %d dead\n", curr_time - philo->start, philo->id);
			exit(0);
		}
	}
	return (NULL);
}

void	lunch_supervisor_routine(pthread_t *th_sup, t_prog *var_prog)
{
	int i;

	i= 0;
	while (i < var_prog->inputs[0])
	{
		pthread_create(&th_sup[i], NULL, &routine_sup, &var_prog->philos[i]);
		i++;
	}
}
