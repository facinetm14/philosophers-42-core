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

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->id % 2 != 0)
			usleep(1000);
		pthread_mutex_init(&philo->l_fork->m_fork, NULL);
		pthread_mutex_init(&philo->r_fork->m_fork, NULL);
		if (philo->l_fork->status == FREE && philo->l_fork->status == FREE)
		{
			pthread_mutex_lock(&philo->l_fork->m_fork);
			pthread_mutex_lock(&philo->r_fork->m_fork);
			philo->l_fork->status = BUSY;
			philo->r_fork->status = BUSY;
			take_fork(philo);
			eat(philo);
			pthread_mutex_unlock(&philo->l_fork->m_fork);
			pthread_mutex_unlock(&philo->r_fork->m_fork);
			philo->l_fork->status = FREE;
			philo->r_fork->status = FREE;
			sleeping(philo);
			think(philo);
		}
		pthread_mutex_destroy(&philo->l_fork->m_fork);
		pthread_mutex_destroy(&philo->r_fork->m_fork);
	}
	return (NULL);
}

void	lunch_philos_runtine(pthread_t *th_sup, t_prog *var_prog)
{
	ft_creat_philos_and_forks(var_prog);
	ft_asign_forks_to_philos(var_prog);
	ft_start_thread_philos(th_sup, var_prog);
}
