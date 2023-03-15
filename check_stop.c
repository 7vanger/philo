/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_stop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopes < vlopes@student.42.rio>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:43:49 by vlopes            #+#    #+#             */
/*   Updated: 2023/03/14 17:25:26 by vlopes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

int	check_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->meal);
	if (philo->table->eaten == philo->table->philosophy)
		philo->table->stop = 1;
	pthread_mutex_unlock(&philo->table->meal);
	pthread_mutex_lock(&philo->table->mutex_stop);
	if (get_time() >= philo->last_meal + philo->time_death)
	{
		philo->table->stop = 1;
		print(philo, "died");
		pthread_mutex_lock(&philo->death_life);
		philo->table->signal = 1;
		pthread_mutex_unlock(&philo->death_life);
	}
	if (philo->table->stop)
	{
		pthread_mutex_unlock(&philo->table->mutex_stop);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->mutex_stop);
	return (0);
}

void	to_one(t_philo *philo)
{
	unsigned long	i;

	i = get_time();
	printf ("%ld 1 has taken a fork\n", (get_time() - i));
	usleep(philo->table->time_death);
	printf ("%d 1 died\n", philo->time_death);
}

int	live_death(int signal, t_philo *philo)
{
	int	str;

	pthread_mutex_lock(&philo->death_life);
	str = signal;
	pthread_mutex_unlock(&philo->death_life);
	return (str);
}

int	eating_three(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < 2)
	{	
		if (check_stop(philo))
			return (1);
		pthread_mutex_lock(&philo->table->forks[philo->fork_l]);
		if (philo->table->forks_int[philo->fork_l])
		{
			philo->table->forks_int[philo->fork_l]--;
			print(philo, "has taken a fork");
			i++;
		}
		pthread_mutex_unlock(&philo->table->forks[philo->fork_l]);
		pthread_mutex_lock(&philo->table->forks[philo->fork_r]);
		if (philo->table->forks_int[philo->fork_r])
		{
			philo->table->forks_int[philo->fork_r]--;
			print(philo, "has taken a fork");
			i++;
		}
		pthread_mutex_unlock(&philo->table->forks[philo->fork_r]);
	}
	return (0);
}
