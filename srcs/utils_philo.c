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

	curr_time = get_time_in_ms();
	philo->last_eat = curr_time + philo->tt_eat;
	printf("%10ld %d is eating \n", curr_time - philo->start, philo->id);
	while (get_time_in_ms() < philo->last_eat)
	{
		usleep(500);
	}
}

void	take_fork(t_philo *philo)
{
	printf("%10ld %d has taken a fork\n",
	get_time_in_ms() - philo->start, philo->id);
	printf("%10ld %d has taken a fork\n",
	get_time_in_ms() - philo->start, philo->id);
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
				curr_time - philo->last_eat) - philo->tt_eat);
	stop_thinking = philo->tt_think + curr_time;
	printf("%10ld %d is thinking\n", curr_time - philo->start, philo->id);
	while (get_time_in_ms() < stop_thinking)
	{
		usleep(100);
	}
}
