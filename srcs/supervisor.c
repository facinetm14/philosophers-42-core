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
	//int		i;
	//int		curr_time;
	
	v_prog = (t_prog *)arg;
	(void)v_prog;
	return (NULL);
}

void	lunch_supervisor_routine(pthread_t *th_sup, t_prog *var_prog)
{
	pthread_create(th_sup, NULL, &routine_sup, var_prog);
}
