/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopes < vlopes@student.42.rio>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:37:37 by vlopes            #+#    #+#             */
/*   Updated: 2023/03/14 18:22:45 by vlopes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

void	exit_threads(t_var *var)
{
	int	i;

	i = 0;
	while (i < var->philosophy)
	{
		pthread_join(var->philo[i].chm, NULL);
		i++;
	}
	i = 0;
	while (i < var->philosophy)
	{
		pthread_mutex_destroy(&var->forks[i]);
		pthread_mutex_destroy(&var->philo[i].death_life);
		i++;
	}
	pthread_mutex_destroy(&var->meal);
	pthread_mutex_destroy(&var->mutex_stop);
	pthread_mutex_destroy(&var->print);
}

void	fun_free(t_var *var)
{
	free(var->philo);
	free(var->forks);
	free(var->forks_int);
}

int	main(int argc, char **argv)
{
	t_var	var;

	var.signal = 0;
	if (argc != 5 && argc != 6)
	{	
		printf("Arguments invalids\n");
		return (0);
	}	
	if (check_args(argv) == 0)
		return (0);
	if (init_var(&var, argv, argc) == 0)
		return (0);
	if (init_philo(&var) == 0)
		return (0);
	if (start(&var))
		return (0);
	return (0);
}
