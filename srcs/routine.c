/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:20:13 by fakouyat          #+#    #+#             */
/*   Updated: 2022/09/07 14:20:13 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*routine(void *arg)
{
	t_philo			*philo;
	pthread_mutex_t	mutex_fork;

	philo = (t_philo *)arg;
	pthread_mutex_init(&mutex_fork, NULL);
	pthread_mutex_lock(&mutex_fork);
	if (!(philo->l_fork->status == FREE && philo->l_fork->status == FREE))
	{
		printf("%d philo %d waiting for fork lf %d - rf %d status (%d - %d)\n", (get_time_in_ms() - philo->start), philo->id, philo->l_fork->id, philo->r_fork->id, philo->l_fork->status, philo->r_fork->status);
		//usleep(100 * 1000);
	}
	if (philo->l_fork->status != BUSY && philo->r_fork->status != BUSY)
	{
		philo->l_fork->status = BUSY;
		philo->r_fork->status = BUSY;
		printf("%d philo %d has taken fork lf %d - rf %d\n", get_time_in_ms() - philo->start, philo->id, philo->l_fork->id, philo->r_fork->id);
	}
	pthread_mutex_unlock(&mutex_fork);
	return (NULL);
}

void	lunch_philos_runtine(t_prog *var_prog)
{
	ft_creat_philos_and_forks(var_prog);
	ft_asign_forks_to_philos(var_prog);
	ft_start_thread_philos(var_prog);
}
