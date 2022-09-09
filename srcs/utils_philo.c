/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 13:37:52 by fakouyat          #+#    #+#             */
/*   Updated: 2022/09/08 13:37:52 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	eat(t_philo *philo)
{
	long	curr_time;
	long	finish;
	curr_time = get_time_in_ms();
	pthread_mutex_lock(&philo->status);
	philo->last_eat = curr_time;
	pthread_mutex_unlock(&philo->status);
	finish = philo->tt_eat + curr_time;
	printf("%10ld %d is eating \n", curr_time - philo->start, philo->id);
	while (get_time_in_ms() < finish)
	{
		usleep(500);
	}
}

void	take_fork(t_philo *philo)
{
	printf("%10ld %d has taken a fork %d\n",
	get_time_in_ms() - philo->start, philo->id, philo->l_fork->id);
	printf("%10ld %d has taken a fork %d\n",
	get_time_in_ms() - philo->start, philo->id, philo->r_fork->id);
}

void	sleeping(t_philo *philo)
{
	long	curr_time;
	long	wake_up;

	curr_time = get_time_in_ms();
	wake_up = curr_time + philo->tt_sleep;
	printf("%10ld %d is sleeping\n", curr_time - philo->start, philo->id);
	while (get_time_in_ms() < wake_up)
	{
		usleep(500);
	}
}

void	think(t_philo *philo)
{
	long	stop_thinking;
	long	curr_time;

	curr_time = get_time_in_ms();
	//if (tt_)
	philo->tt_think = (philo->tt_die - (
				curr_time - philo->last_eat) - philo->tt_eat) / 2;
	stop_thinking = philo->tt_think + curr_time;
	if (philo->tt_think < 0)
		philo->tt_think = 0;
	else if (philo->tt_think > 600)
		philo->tt_think = 200;
	printf("%10ld %d is thinking for %ld\n", curr_time - philo->start, philo->id, philo->tt_think);
	while (get_time_in_ms() < stop_thinking)
	{
		usleep(100);
	}
}
