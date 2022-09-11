/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:04:26 by fakouyat          #+#    #+#             */
/*   Updated: 2022/09/07 15:04:26 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	one_philo_routine(t_prog *v_prog)
{
	long	curr_time;

	curr_time = get_time_in_ms();
	if (v_prog->inputs[0] == 1)
	{
		pthread_mutex_lock(&v_prog->philos[0].m_stop);
		v_prog->philos[0].end = STOP;
		pthread_mutex_unlock(&v_prog->philos[0].m_stop);
		printf("%10ld %d has taken a fork\n",
			curr_time - v_prog->philos[0].start, v_prog->philos[0].id);
		printf("%10ld %d die\n", v_prog->philos[0].tt_die, v_prog->philos[0].id);
		return (0);
	}
	return (1);
}

static int	ft_potential_death_or_stop(long diff_time, t_prog *v_prog)
{
	if (diff_time - TIME_LOST >= v_prog->philos[v_prog->count[0]].tt_die
		|| v_prog->count[2] == 0)
	{
		v_prog->count[1] = 0;
		while (v_prog->count[1] < v_prog->inputs[0])
		{
			pthread_mutex_lock(&v_prog->philos[v_prog->count[1]].m_stop);
			v_prog->philos[v_prog->count[1]].end = STOP;
			pthread_mutex_unlock(&v_prog->philos[v_prog->count[1]].m_stop);
			v_prog->count[1] += 1;
		}
		if (v_prog->count[2] == 0)
			return (0);
		pthread_mutex_lock(&v_prog->print_mutex);
		printf("%10ld %d die\n",
			v_prog->now - v_prog->philos[v_prog->count[0]].start - TIME_LOST,
			v_prog->philos[v_prog->count[0]].id);
		pthread_mutex_unlock(&v_prog->print_mutex);
		return (0);
	}
	return (1);
}

void	*routine_sup(void *arg)
{
	t_prog	*v_prog;
	long	diff_time;

	v_prog = (t_prog *)arg;
	v_prog->count[2] = v_prog->inputs[0];
	if (one_philo_routine(v_prog) == 0)
		return (NULL);
	while (1)
	{
		v_prog->now = get_time_in_ms();
		v_prog->count[0] = 0;
		while (v_prog->count[0] < v_prog->inputs[0])
		{
			ft_check_nbt_eaten(&diff_time, v_prog);
			if (ft_potential_death_or_stop(diff_time, v_prog) == 0)
				return (NULL);
			v_prog->count[0] += 1;
		}
	}
	return (NULL);
}

void	lunch_supervisor_routine(pthread_t *th_sup, t_prog *var_prog)
{
	pthread_create(th_sup, NULL, &routine_sup, var_prog);
}
