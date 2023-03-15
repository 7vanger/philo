/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopes < vlopes@student.42.rio>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:05:11 by vlopes            #+#    #+#             */
/*   Updated: 2023/03/14 18:22:24 by vlopes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				time_death;
	int				time_eat;
	int				sleep_time;
	int				ate;
	int				fork_l;
	int				fork_r;
	pthread_mutex_t	death_life;
	unsigned long	last_meal;
	struct s_var	*table;
	pthread_t		chm;
}				t_philo;

typedef struct s_var
{
	int				time_death;
	int				time_eat;
	int				sleep_time;
	int				eat_count;
	int				philosophy;
	int				eaten;
	int				stop;
	int				signal;
	unsigned long	start_program;
	pthread_mutex_t	*forks;
	int				*forks_int;
	pthread_mutex_t	print;
	pthread_mutex_t	mutex_stop;
	pthread_mutex_t	meal;
	t_philo			*philo;
}					t_var;

int				init_philo(t_var *var);
int				init_var(t_var *var, char **argv, int argc);
int				atoi_philo(char *str);
int				check_args(char **argv);
int				eating(t_philo *philo);
unsigned long	get_time(void);
void			print(t_philo *philo, char *str);
int				sleeping(t_philo *philo);
int				smart_sleep(int j, t_philo *philo);
void			monitoring(t_var *var);
int				call_mutex(t_var *var);
void			thiking(t_philo *philo);
void			exit_threads(t_var *var);
void			fun_free(t_var *var);
int				start(t_var *var);
int				check_stop(t_philo *philo);
void			to_one(t_philo *philo);
int				live_death(int signal, t_philo *philo);
int				eating_three(t_philo *philo);

#endif
