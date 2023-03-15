/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopes < vlopes@student.42.rio>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:36:52 by vlopes            #+#    #+#             */
/*   Updated: 2023/03/14 17:38:04 by vlopes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

int	check_elements(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] <= 47 || argv[i][j] >= 58)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	atoi_philo(char *str)
{
	int	i;
	int	rec;

	i = 0;
	rec = 0;
	while (str[i])
	{
		rec = rec * 10 + (str[i] - '0');
		i++;
	}
	return (rec);
}	

int	check_args(char **argv)
{
	int	i;

	i = 1;
	if (check_elements(argv) == 0)
	{
		printf("Error charcter\n");
		return (0);
	}
	while (argv[i])
	{
		if (2147483647 - atoi_philo(argv[i]) < 0
			|| atoi_philo(argv[i]) == 0)
		{
			printf("Error in elements\n");
			return (0);
		}
		i++;
	}
	return (1);
}
