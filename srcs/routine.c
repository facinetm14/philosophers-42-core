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
	int				has_eaten;

	has_eaten = 0;
	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->id % 2 != 0)
			usleep(1000);
		pthread_mutex_lock(&philo->l_fork->m_fork);
		if (philo->l_fork->status == FREE && philo->r_fork->status == FREE)
		{
			philo->l_fork->status = BUSY;
			pthread_mutex_lock(&philo->r_fork->m_fork);
			philo->r_fork->status = BUSY;
			take_fork(philo);
			eat(philo);
			has_eaten = 1;
			philo->l_fork->status = FREE;
			philo->r_fork->status = FREE;
			pthread_mutex_unlock(&philo->r_fork->m_fork);

		}
		pthread_mutex_unlock(&philo->l_fork->m_fork);
		if (has_eaten == 1)
		{
			sleeping(philo);
			think(philo);
			has_eaten = 0;
		}
	}
	return (NULL);
}

void	lunch_philos_runtine(pthread_t *th_sup, t_prog *var_prog)
{
	ft_creat_philos_and_forks(var_prog);
	ft_asign_forks_to_philos(var_prog);
	ft_start_thread_philos(th_sup, var_prog);
}
