/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopes < vlopes@student.42.rio>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 20:34:06 by vlopes            #+#    #+#             */
/*   Updated: 2023/03/14 16:10:39 by vlopes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * (unsigned long)1000 + time.tv_usec / 1000);
}

int	smart_sleep(int time, t_philo *philo)
{
	unsigned long	i;

	i = get_time();
	while ((get_time() - i) < (unsigned long)time)
	{
		if (check_stop(philo))
			return (1);
		usleep(150);
	}
	return (0);
}

int	call_mutex(t_var *var)
{
	int	i;

	i = 0;
	pthread_mutex_init(&var->print, NULL);
	pthread_mutex_init(&var->mutex_stop, NULL);
	pthread_mutex_init(&var->meal, NULL);
	while (i < var->philosophy)
	{
		if (pthread_mutex_init(&var->philo[i].death_life, NULL))
			return (0);
		if (pthread_mutex_init(&var->forks[i], NULL))
			return (0);
		i++;
	}
	return (1);
}
