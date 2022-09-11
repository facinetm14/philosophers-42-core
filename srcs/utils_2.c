/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 03:20:19 by fakouyat          #+#    #+#             */
/*   Updated: 2022/09/11 03:20:19 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_continue_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_stop);
	if (philo->end == STOP)
	{
		pthread_mutex_unlock(&philo->m_stop);
		return (0);
	}
	pthread_mutex_unlock(&philo->m_stop);
	return (1);
}

void	ft_check_nbt_eaten(long *diff_time, t_prog *v_prog)
{
	pthread_mutex_lock(&v_prog->philos[v_prog->count[0]].status);
	*diff_time = v_prog->now - v_prog->philos[v_prog->count[0]].last_eat;
	if (v_prog->philos[v_prog->count[0]].nbt_eat == 0)
	{
		v_prog->count[2] -= 1;
		v_prog->philos[v_prog->count[0]].nbt_eat -= 1;
	}
	pthread_mutex_unlock(&v_prog->philos[v_prog->count[0]].status);
}
