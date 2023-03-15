/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopes < vlopes@student.42.rio>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:19:56 by vlopes            #+#    #+#             */
/*   Updated: 2023/03/14 16:04:38 by vlopes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

static int	eating_two(t_philo *philo)
{
	print(philo, "is eating");
	philo->last_meal = get_time();
	philo->ate++;
	if (philo->ate == philo->table->eat_count)
	{
		pthread_mutex_lock(&philo->table->meal);
		philo->table->eaten++;
		pthread_mutex_unlock(&philo->table->meal);
	}
	if (smart_sleep(philo->time_eat, philo))
		return (1);
	pthread_mutex_lock(&philo->table->forks[philo->fork_l]);
	philo->table->forks_int[philo->fork_l]++;
	pthread_mutex_unlock(&philo->table->forks[philo->fork_l]);
	pthread_mutex_lock(&philo->table->forks[philo->fork_r]);
	philo->table->forks_int[philo->fork_r]++;
	pthread_mutex_unlock(&philo->table->forks[philo->fork_r]);
	return (0);
}

int	eating(t_philo *philo)
{
	if (eating_three(philo))
		return (1);
	if (eating_two(philo))
		return (1);
	return (0);
}

void	print(t_philo *philo, char	*str)
{
	pthread_mutex_lock(&philo->table->print);
	if (live_death(philo->table->signal, philo) == 0)
		printf("%ld %d %s\n", get_time() - philo->table->start_program,
			philo->id, str);
	pthread_mutex_unlock(&philo->table->print);
}

int	sleeping(t_philo *philo)
{
	print(philo, "is sleeping");
	if (smart_sleep(philo->sleep_time, philo))
		return (1);
	return (0);
}

void	thiking(t_philo *philo)
{
	print(philo, "is thinking");
}
