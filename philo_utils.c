/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponnusa <tponnusa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 13:12:57 by tponnusa          #+#    #+#             */
/*   Updated: 2023/10/13 18:23:24 by tponnusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_display_message(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	ft_atoi(char *str)
{
	unsigned int	i;
	long int		val;

	i = 0;
	val = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			val = (val * 10) + str[i] - '0';
		else
			return (0);
		i++;
	}
	if (val < 0 || val > INT_MAX || str[i] != '\0')
		return (0);
	return (val);
}

int	is_valid_input(int ac, char **av)
{
	int	i;
	int	no_of_args;

	i = 1;
	no_of_args = 4;
	if (ac == 6)
		no_of_args = 5;
	while (i <= no_of_args)
	{
		if (!ft_atoi(av[i]))
			return (0);
		i++;
	}	
	return (1);
}

size_t	get_time_ms(void)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) == -1)
		return (-1);
	return ((current_time.tv_sec * 1000)
		+ (current_time.tv_usec / 1000));
}

void	calculate_usleep(useconds_t end_sleep)
{
	u_int64_t	start_to_sleep;

	start_to_sleep = get_time_ms();
	while ((get_time_ms() - start_to_sleep) < end_sleep)
		usleep(end_sleep / 10);
}
