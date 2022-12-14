/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:38:08 by fakouyat          #+#    #+#             */
/*   Updated: 2022/09/07 12:38:08 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	is_args_int(int lenght, char *argv[])
{
	int	i;
	int	j;

	i = 0;
	while (i < lenght)
	{
		j = 0;
		while (argv[i + 1][j] != '\0')
		{
			if (!(argv[i + 1][j] >= '0' && argv[i + 1][j] <= '9'))
			{
				if (!(argv[i + 1][j] == '-' && j == 0))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

static int	ft_atoi(const char *str)
{
	int		i;
	long	sign;
	long	number;
	long	result;

	i = 0;
	sign = 1;
	number = 0;
	while (str[i] == 32 || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = (number * 10) + (str[i] - '0');
		i++;
	}
	result = sign * number;
	if (result < -2147483648 || result > 2147483647)
		return (0);
	return ((int)number * sign);
}

int	ft_parsing(int lenght, char **argv, t_prog *var_prog)
{
	int	i;

	i = 0;
	while (i + 1 < lenght)
	{
		var_prog->inputs[i] = ft_atoi(argv[i + 1]);
		if (var_prog->inputs[i] <= 0 && ft_strlen(argv[i + 1]) != 1)
		{
			printf("Error : Wrong arguments !\n");
			return (0);
		}
		i++;
	}
	if (var_prog->inputs[0] < 1 || var_prog->inputs[0] >= MAX_PHILO + 1)
	{
		printf("Error : number of philoshophers must be between 1 and 200 !\n");
		return (0);
	}
	if (lenght == 5)
		var_prog->inputs[4] = -1;
	if (var_prog->inputs[4] == 0)
		return (-1);
	return (1);
}
