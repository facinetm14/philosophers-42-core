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
		usleep(1000);
		pthread_mutex_lock(&philo->m_stop);
		if (philo->end == STOP)
		{
			pthread_mutex_unlock(&philo->m_stop);
			break ;
		}
		pthread_mutex_unlock(&philo->m_stop);
		pthread_mutex_lock(&philo->l_fork->m_fork);
        pthread_mutex_lock(&philo->r_fork->m_fork);
		pthread_mutex_lock(&philo->m_stop);
		if (philo->end != STOP)
			take_fork(philo);
		pthread_mutex_unlock(&philo->m_stop);
		pthread_mutex_lock(&philo->m_stop);
        if (philo->end != STOP)
			eat(philo);
		pthread_mutex_unlock(&philo->m_stop);
        pthread_mutex_unlock(&philo->r_fork->m_fork);
        pthread_mutex_unlock(&philo->l_fork->m_fork);
		pthread_mutex_lock(&philo->m_stop);
		if (philo->end != STOP)
        	sleeping(philo);
		pthread_mutex_unlock(&philo->m_stop);
		pthread_mutex_lock(&philo->m_stop);
		if (philo->end != STOP)
        	think(philo);
		pthread_mutex_unlock(&philo->m_stop);
		pthread_mutex_lock(&philo->m_stop);
		if (philo->end == STOP)
		{
			pthread_mutex_unlock(&philo->m_stop);
			break ;
		}
		pthread_mutex_unlock(&philo->m_stop);
	}
	return (NULL);
}

void	lunch_philos_runtine(pthread_t *th_sup, t_prog *var_prog)
{
	ft_creat_philos_and_forks(var_prog);
	ft_asign_forks_to_philos(var_prog);
	ft_start_thread_philos(th_sup, var_prog);
}
