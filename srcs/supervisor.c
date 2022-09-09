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

void	*routine_sup(void *arg)
{
	t_prog	*v_prog;
	int counter[3];
	long	curr_time;
	long	diff_time;

	counter[2] = 0;
	v_prog = (t_prog *)arg;
	while (1)
	{
		counter[0] = 0;
		curr_time = get_time_in_ms();
		while (counter[0] < v_prog->inputs[0])
		{
			pthread_mutex_lock(&v_prog->philos[counter[0]].status);
			diff_time = curr_time - v_prog->philos[counter[0]].last_eat;
			pthread_mutex_unlock(&v_prog->philos[counter[0]].status);
			if (diff_time >= v_prog->philos[counter[0]].tt_die)
			{
				counter[1] = 0;
				while (counter[1] < v_prog->inputs[0])
				{
					pthread_mutex_lock(&v_prog->philos[counter[1]].m_stop);
					v_prog->philos[counter[1]].end = STOP;
					pthread_mutex_unlock(&v_prog->philos[counter[1]].m_stop);
					counter[1] += 1;
				}
				printf("%10ld %d die\n", curr_time - v_prog->philos[counter[0]].start, v_prog->philos[counter[0]].id);
				counter[2] = STOP;
				break ;
			}
			counter[0] += 1;
		}
		if (counter[2] == STOP)
			break;
	}
	// if (counter[2] == STOP)
	// 	printf("%10ld %d die\n", curr_time - v_prog->philos[counter[0]].start, v_prog->philos[counter[0]].id);
	return (NULL);
}

void	lunch_supervisor_routine(pthread_t *th_sup, t_prog *var_prog)
{
	pthread_create(th_sup, NULL, &routine_sup, var_prog);
}
