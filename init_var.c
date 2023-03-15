/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopes < vlopes@student.42.rio>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:00:47 by vlopes            #+#    #+#             */
/*   Updated: 2023/03/14 18:23:07 by vlopes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

static void	cont(t_var *var, char **argv, int argc)
{
	var->philosophy = atoi_philo(argv[1]);
	var->time_death = atoi_philo(argv[2]);
	var->time_eat = atoi_philo(argv[3]);
	var->sleep_time = atoi_philo(argv[4]);
	if (argc == 6)
		var->eat_count = atoi_philo(argv[5]);
	else
		var->eat_count = 0;
	var->eaten = 0;
	var->stop = 0;
}

int	init_var(t_var *var, char **argv, int argc)
{
	int	i;

	i = 0;
	cont(var, argv, argc);
	var->philo = malloc(sizeof(t_philo) * var->philosophy);
	if (!var->philo)
	{
		free(var->philo);
		return (0);
	}	
	var->forks = malloc(sizeof(pthread_mutex_t) * var->philosophy);
	if (!var->forks)
	{	
		free(var->forks);
		return (0);
	}	
	var->forks_int = malloc(sizeof(int) * var->philosophy);
	while (i < var->philosophy)
	{
		var->forks_int[i] = 1;
		i++;
	}
	return (1);
}

void	*routine(void *str)
{
	t_philo	*philo;

	philo = (t_philo *)str;
	if (philo->id % 2 == 0 && philo->table->philosophy > 1)
		usleep(1000);
	while (1)
	{
		if (philo->table->philosophy == 1)
		{
			to_one(philo);
			break ;
		}
		else
		{		
			if (eating(philo))
				break ;
			if (sleeping(philo))
				break ;
			thiking(philo);
		}	
	}
	return (NULL);
}

int	init_philo(t_var *var)
{
	int	i;

	if (!call_mutex(var))
		return (0);
	i = 0;
	while (i < var->philosophy)
	{
		var->philo[i].id = i + 1;
		var->philo[i].ate = 0;
		var->philo[i].fork_l = i;
		var->philo[i].table = var;
		var->philo[i].time_death = var->time_death;
		var->philo[i].time_eat = var->time_eat;
		var->philo[i].sleep_time = var->sleep_time;
		var->philo[i].fork_r = (i + 1) % var->philosophy;
		i++;
	}
	return (1);
}

int	start(t_var *var)
{
	int	i;

	i = 0;
	var->start_program = get_time();
	while (i < var->philosophy)
	{
		var->philo[i].last_meal = get_time();
		if (pthread_create(&var->philo[i].chm, NULL, routine, &var->philo[i]))
			return (0);
		i++;
	}
	exit_threads(var);
	fun_free(var);
	return (1);
}
