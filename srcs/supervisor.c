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
	int counter[2];
	long	curr_time;
	long	diff_time;

	v_prog = (t_prog *)arg;
	while (1)
	{
		curr_time = get_time_in_ms();
		if (v_prog->inputs[0] == 1)
		{
	
			pthread_mutex_lock(&v_prog->philos[0].m_stop);
			v_prog->philos[0].end = STOP;
			pthread_mutex_unlock(&v_prog->philos[0].m_stop);
			printf("%10ld %d has taken a fork\n",
					curr_time - v_prog->philos[0].start, v_prog->philos[0].id);
				printf("%10ld %d die\n", v_prog->philos[0].tt_die, v_prog->philos[0].id);
			return (NULL) ;
		}
		counter[0] = 0;
		while (counter[0] < v_prog->inputs[0])
		{
			pthread_mutex_lock(&v_prog->philos[counter[0]].status);
			diff_time = curr_time - v_prog->philos[counter[0]].last_eat;
			pthread_mutex_unlock(&v_prog->philos[counter[0]].status);
			if (diff_time >= v_prog->philos[counter[0]].tt_die)
			{
				counter[1] = 0;
				while (counter[1] < v_prog->inputs[0] )
				{
					pthread_mutex_lock(&v_prog->philos[counter[1]].m_stop);
					v_prog->philos[counter[1]].end = STOP;
					pthread_mutex_unlock(&v_prog->philos[counter[1]].m_stop);
					counter[1] += 1;
				}
				printf("%10ld %d die\n", curr_time - v_prog->philos[counter[0]].start, v_prog->philos[counter[0]].id);
				return (NULL) ;
			}
			counter[0] += 1;
		}
	}
	// if (counter[2] == STOP)
	// 	printf("%10ld %d die\n", curr_time - v_prog->philos[counter[0]].start, v_prog->philos[counter[0]].id);
	return (NULL);
}

void	lunch_supervisor_routine(pthread_t *th_sup, t_prog *var_prog)
{
	pthread_create(th_sup, NULL, &routine_sup, var_prog);
}
