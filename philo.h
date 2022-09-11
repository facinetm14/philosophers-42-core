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
# define STOP 100

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	m_fork;
}				t_fork;

typedef struct s_philo
{
	int				id;
	long			tt_die;
	long			tt_eat;
	long			tt_sleep;
	long			tt_think;
	t_fork			*l_fork;
	t_fork			*r_fork;
	int				nbt_eat;
	long			last_eat;
	pthread_mutex_t	status;
	pthread_mutex_t	m_stop;
	long			end;
	long			start;
}				t_philo;
typedef struct s_prog
{
	pthread_t		th_philos[MAX_PHILO];
	t_fork			forks[MAX_PHILO];
	t_philo			philos[MAX_PHILO];
	long			start;
	int				inputs[5];
	int				count[3];
	long			now;
	pthread_mutex_t	print_mutex;
}				t_prog;

/* utils.c */
int		is_args_int(int lenght, char *argv[]);
int		ft_parsing(int lenght, char **argv, t_prog *var_prog);
/* check_input.c */
int		ft_check_input(int argc, char **argv, t_prog *var_prog);
/* routin.c */
void	*routine(void *arg);
void	lunch_philos_runtine(pthread_t *th_sup, t_prog *var_prog);
/* timing.c */
long	get_time_in_ms(void);
/* utils_prog.c */
void	ft_asign_forks_to_philos(t_prog *var_prog);
void	ft_creat_philos_and_forks(t_prog *var_prog);
void	ft_start_thread_philos(pthread_t *th_sup, t_prog *var_prog);
void	ft_destroy_mutexes(t_prog *v_prog);
/*supervisor.c*/
void	lunch_supervisor_routine(pthread_t *th_sup, t_prog *var_prog);
void	*routine_sup(void *arg);
/* utils_philo */
void	eat(t_philo *philo);
void	take_fork(t_philo *philo);
void	sleeping(t_philo *philo);
void	think(t_philo *philo);
/* utils_2 */
int		ft_continue_routine(t_philo *philo);
void	ft_check_nbt_eaten(long *diff_time, t_prog *v_prog);
#endif