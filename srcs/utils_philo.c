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
	printf("%10ld philo %d is eating \n", curr_time - philo->start, philo->id);
	while (get_time_in_ms() < philo->last_eat)
	{
		usleep(50);
	}
	philo->l_fork->status = FREE;
	philo->r_fork->status = FREE;
}

void	take_fork(t_philo *philo)
{
	printf("%10ld philo %d has taken a fork %d\n",
		get_time_in_ms() - philo->start, philo->id, philo->l_fork->id);
	printf("%10ld philo %d has taken a fork %d\n",
		get_time_in_ms() - philo->start, philo->id, philo->r_fork->id);
}

void	sleeping(t_philo *philo)
{
	long	curr_time;
	long	wake_up;

	curr_time = get_time_in_ms();
	wake_up = curr_time + philo->tt_sleep;
	printf("%10ld philo %d is sleeping\n", curr_time - philo->start, philo->id);
	while (get_time_in_ms() < wake_up)
	{
		usleep(50);
	}
}

void	think(t_philo *philo)
{
	long	stop_thinking;
	long	curr_time;

	curr_time = get_time_in_ms();
	philo->tt_think = (philo->tt_die - (
				curr_time - philo->last_eat) - philo->tt_eat);
	stop_thinking = philo->tt_think + curr_time;
	printf("%10ld %d is thinking\n", curr_time - philo->start, philo->id);
	while (get_time_in_ms() < stop_thinking)
	{
		usleep(50);
	}
}
