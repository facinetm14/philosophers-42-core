/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_prog.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:28:17 by fakouyat          #+#    #+#             */
/*   Updated: 2022/09/07 14:28:17 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_asign_forks_to_philos(t_prog *var_prog)
{
	int	i;

	i = 0;
	while (i < var_prog->inputs[0])
	{
		if (i == 0)
			var_prog->philos[i].l_fork = &var_prog->forks[4];
		else
			var_prog->philos[i].l_fork = &var_prog->forks[i - 1];
		var_prog->philos[i].r_fork = &var_prog->forks[i];
		pthread_mutex_init(&var_prog->forks[i].m_fork, NULL);
		pthread_mutex_init(&var_prog->philos[i].status, NULL);
		pthread_mutex_init(&var_prog->philos[i].m_stop, NULL);
		i++;
	}
}

void	ft_creat_philos_and_forks(t_prog *var_prog)
{
	t_philo	tmp_philo;
	t_fork	tmp_fork;
	int		i;

	i = 0;
	while (i < var_prog->inputs[0])
	{
		tmp_philo.id = i + 1;
		tmp_philo.end = 0;
		tmp_philo.start = var_prog->start;
		tmp_philo.tt_die = (long)var_prog->inputs[1];
		tmp_philo.tt_eat = (long)var_prog->inputs[2];
		tmp_philo.tt_sleep = (long)var_prog->inputs[3];
		tmp_philo.nbt_eat = var_prog->inputs[4];
		tmp_philo.last_eat = tmp_philo.start;
		tmp_fork.id = i + 1;
		var_prog->forks[i] = tmp_fork;
		var_prog->philos[i] = tmp_philo;
		i++;
	}
}

void	ft_start_thread_philos(pthread_t *th_sup, t_prog *var_prog)
{
	int	i;

	i = 0;
	while (i < var_prog->inputs[0])
	{
		pthread_create(&(var_prog->th_philos[i]), NULL,
			&routine, (&var_prog->philos[i]));
		i++;
	}
	lunch_supervisor_routine(th_sup, var_prog);
	i = 0;
	while (i < var_prog->inputs[0])
	{
		pthread_join(var_prog->th_philos[i], NULL);
		i++;
	}
	pthread_join(*th_sup, NULL);
}

void	ft_destroy_mutexes(t_prog *v_prog)
{
	int	i;

	i = 0;
	while (i < v_prog->inputs[0])
	{
		pthread_mutex_destroy(&v_prog->forks[i].m_fork);
		pthread_mutex_destroy(&v_prog->philos[i].status);
		pthread_mutex_destroy(&v_prog->philos[i].m_stop);
		i++;
	}
}
