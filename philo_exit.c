/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponnusa <tponnusa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 13:11:19 by tponnusa          #+#    #+#             */
/*   Updated: 2023/10/17 11:04:35 by tponnusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_error(int err_no)
{
	if (err_no == 1)
		ft_display_message("Error:\n Arguments allowed MIN-4 | MAX-5\n Input Format:\n\
			No of philos \ttime_to_die(ms)\t time_to_eat(ms)\ttime_to_sleep(ms)\
			No_of_time_must_eat[optional]\n", 2);
	else if (err_no == 2)
		ft_display_message("Error:\n Invalid input\n Input must be > 0", 2);
	else if (err_no == 3)
		ft_display_message("Error:\n Unable to get time by System", 2);
	else if (err_no == 4)
		ft_display_message("Error:\n Unable to ALLOCATE memory for threads", 2);
	else if (err_no == 5)
		ft_display_message("Error:\n Unable to ALLOCATE memory for Mutexes", 2);
	exit(EXIT_FAILURE);
}

void	destroy_fork_mutexes(t_input *input, int tot_created)
{
	int	i;

	i = 0;
	while (i < tot_created)
	{
		pthread_mutex_destroy(&input ->forks[i]);
		i++;
	}
}

void	destroy_sign_mutexes(t_input *input, int tot_created)
{
	int	i;

	i = 0;
	while (i < tot_created)
	{
		pthread_mutex_destroy(&input ->sign_mutex[i]);
		i++;
	}
}

void	exit_error_free(t_input *input, int err_no)
{
	if (err_no == 1)
		ft_display_message("Error:\n Unable to CREATE threads by System", 2);
	else if (err_no == 2)
		ft_display_message("Error:\n Unable to JOIN threads by System", 2);
	free_all(input);
	exit(EXIT_FAILURE);
}

void	exit_error_free2(t_input *input, int tot_created, int err_no)
{
	ft_display_message("Error:\n Unable to initialize MUTEX by System", 2);
	if (err_no == 1)
		destroy_fork_mutexes(input, tot_created);
	else if (err_no == 2)
	{
		destroy_fork_mutexes(input, input -> no_of_philos);
		destroy_sign_mutexes(input, tot_created);
	}
	else if (err_no == 3)
	{
		destroy_fork_mutexes(input, input -> no_of_philos);
		destroy_sign_mutexes(input, input -> no_of_philos);
	}
	if (input -> philos)
		free(input -> philos);
	if (input -> forks)
		free(input -> forks);
	if (input -> sign_mutex)
		free(input -> sign_mutex);
	exit(EXIT_FAILURE);
}
