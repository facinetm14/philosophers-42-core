/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 17:21:07 by fakouyat          #+#    #+#             */
/*   Updated: 2022/09/05 17:21:07 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

# define MAX_PHILO 201
# define FREE 0
# define BUSY 1

typedef struct s_fork
{
	int	id;
	int	status;
}				t_fork;
typedef struct s_philo
{
	int		id;
	int		tt_die;
	int		tt_eat;
	int		tt_sleep;
	t_fork	*l_fork;
	t_fork	*r_fork;
	int		nbt_eat;
	int		last_eat;
	int		status;
	int		start;
}				t_philo;
typedef struct s_prog
{
	pthread_t	th_philos[MAX_PHILO];
	t_fork		forks[MAX_PHILO];
	t_philo		philos[MAX_PHILO];
	int			start;
	int			inputs[5];

}				t_prog;

/* utils.c */
int		is_args_int(int lenght, char *argv[]);
void	ft_parsing(int lenght, char **argv, t_prog *var_prog);
/* check_input.c */
void	ft_check_input(int argc, char **argv, t_prog *var_prog);
/* routin.c */
void	*routine(void *arg);
void	lunch_philos_runtine(t_prog *var_prog);
/* timing.c */
int		get_time_in_ms(void);
/* utils_prog.c */
void	ft_asign_forks_to_philos(t_prog *var_prog);
void	ft_creat_philos_and_forks(t_prog *var_prog);
void	ft_start_thread_philos(t_prog *var_prog);

#endif