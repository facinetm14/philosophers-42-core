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
	philo->last_eat = get_time_in_ms();
	if (philo->nbt_eat > 0)
		philo->nbt_eat -= 1;
	pthread_mutex_unlock(&philo->status);
	finish = philo->tt_eat + curr_time;
	if (ft_continue_routine(philo) == 0)
		return ;
	pthread_mutex_lock(philo->print_mutex);
	printf("%10ld %d is eating \n", curr_time - philo->start, philo->id);
	pthread_mutex_unlock(philo->print_mutex);
	while (get_time_in_ms() < finish)
	{
		if (ft_continue_routine(philo) == 0)
			return ;
		usleep(500);
	}
}

void	take_fork(t_philo *philo)
{
	if (ft_continue_routine(philo) == 0)
		return ;
	pthread_mutex_lock(philo->print_mutex);
	printf("%10ld %d has taken a fork\n",
		get_time_in_ms() - philo->start, philo->id);
	printf("%10ld %d has taken a fork\n",
		get_time_in_ms() - philo->start, philo->id);
	pthread_mutex_unlock(philo->print_mutex);
}

void	sleeping(t_philo *philo)
{
	long	curr_time;
	long	wake_up;

	curr_time = get_time_in_ms();
	wake_up = curr_time + philo->tt_sleep;
	if (ft_continue_routine(philo) == 0)
		return ;
	pthread_mutex_lock(philo->print_mutex);
	printf("%10ld %d is sleeping\n", curr_time - philo->start, philo->id);
	pthread_mutex_unlock(philo->print_mutex);
	while (get_time_in_ms() < wake_up)
	{
		if (ft_continue_routine(philo) == 0)
			return ;
		usleep(500);
	}
}

void	think(t_philo *philo)
{
	long	stop_thinking;
	long	curr_time;

	curr_time = get_time_in_ms();
	if (ft_continue_routine(philo) == 0)
		return ;
	pthread_mutex_lock(&philo->status);
	philo->tt_think = (philo->tt_die - (
				get_time_in_ms() - philo->last_eat) - philo->tt_eat) / 2;
	if (philo->tt_think < 0)
		philo->tt_think = 0;
	if (philo->tt_think > 600)
		philo->tt_think = 200;
	stop_thinking = philo->tt_think + curr_time;
	pthread_mutex_unlock(&philo->status);
	pthread_mutex_lock(philo->print_mutex);
	printf("%10ld %d is thinking\n", curr_time - philo->start, philo->id);
	pthread_mutex_unlock(philo->print_mutex);
	while (get_time_in_ms() < stop_thinking)
	{
		if (ft_continue_routine(philo) == 0)
			return ;
		usleep(500);
	}
}
