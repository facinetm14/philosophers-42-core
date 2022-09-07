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
		if (i == 4)
			var_prog->philos[i].r_fork = &var_prog->forks[0];
		else
			var_prog->philos[i].r_fork = &var_prog->forks[i];
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
		tmp_philo.start = var_prog->start;
		tmp_fork.id = i + 1;
		tmp_fork.status = FREE;
		var_prog->forks[i] = tmp_fork;
		var_prog->philos[i] = tmp_philo;
		i++;
	}
}

void	ft_start_thread_philos(t_prog *var_prog)
{
	int	i;

	i = 0;
	while (i < var_prog->inputs[0])
	{
		pthread_create(&(var_prog->th_philos[i]), NULL,
			&routine, (&var_prog->philos[i]));
		i++;
	}
	i = 0;
	while (i < var_prog->inputs[0])
	{
		pthread_join(var_prog->th_philos[i], NULL);
		i++;
	}
}