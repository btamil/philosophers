/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponnusa <tponnusa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 13:24:20 by tponnusa          #+#    #+#             */
/*   Updated: 2023/10/13 18:26:05 by tponnusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	alloc_mutexes(t_input *input)
{
	int	i;

	input -> forks = malloc(sizeof(pthread_mutex_t) * input->no_of_philos);
	input -> sign_mutex = malloc(sizeof(pthread_mutex_t) * input->no_of_philos);
	if (input -> forks == NULL || input -> sign_mutex == NULL)
	{
		free(input -> philos);
		if (input -> forks)
			free(input -> forks);
		exit_error(5);
	}
	i = 0;
	while (i < input-> no_of_philos)
	{
		if (pthread_mutex_init(&input -> forks[i], NULL) != 0)
			exit_error_free2(input, i, 1);
		i++;
	}
	i = 0;
	while (i < input-> no_of_philos)
	{
		if (pthread_mutex_init(&input -> sign_mutex[i], NULL) != 0)
			exit_error_free2(input, i, 2);
		i++;
	}
}

void	initialize_mutexes(t_input *input)
{
	if (pthread_mutex_init(&input -> mutex_print, NULL) != 0)
		exit_error_free2(input, input-> no_of_philos, 3);
	if (pthread_mutex_init(&input -> mutex_eat, NULL) != 0)
	{
		pthread_mutex_destroy(&input -> mutex_print);
		exit_error_free2(input, input-> no_of_philos, 3);
	}
	if (pthread_mutex_init(&input -> mutex_last_meal, NULL) != 0)
	{
		pthread_mutex_destroy(&input -> mutex_print);
		pthread_mutex_destroy(&input -> mutex_eat);
		exit_error_free2(input, input-> no_of_philos, 3);
	}
	if (pthread_mutex_init(&input -> mutex_die, NULL) != 0)
	{
		pthread_mutex_destroy(&input -> mutex_print);
		pthread_mutex_destroy(&input -> mutex_eat);
		pthread_mutex_destroy(&input -> mutex_last_meal);
		exit_error_free2(input, input-> no_of_philos, 3);
	}
}

void	alloc_assign_arrays(t_input *input)
{
	int	i;

	input ->fork_at_hand = malloc(sizeof(int) * input ->no_of_philos);
	input ->sign = malloc(sizeof(int) * input ->no_of_philos);
	if (input ->fork_at_hand == NULL || input ->sign == NULL)
	{
		free_all(input);
		exit_error(4);
	}
	i = 0;
	while (i < input->no_of_philos)
	{
		input -> fork_at_hand[i] = -1;
		input -> sign[i] = -1;
		i++;
	}
}

void	initialize_input(t_input *input, int ac, char **av)
{
	int64_t	time;

	input->no_of_philos = ft_atoi(av[1]);
	input->time_to_die = ft_atoi(av[2]);
	input->time_to_eat = ft_atoi(av[3]);
	input->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		input->max_eat_count = ft_atoi(av[5]);
	else
		input->max_eat_count = -1;
	input->is_alive = 1;
	time = get_time_ms();
	if (time == -1)
		exit_error(3);
	else
		input -> start_time = time;
	input -> philos = malloc(sizeof(t_philo) * input->no_of_philos);
	if (input->philos == NULL)
		exit_error(4);
	alloc_mutexes(input);
	initialize_mutexes(input);
	alloc_assign_arrays(input);
}

void	initialize_philo(t_input *input)
{
	int	i;

	i = 0;
	while (i < input->no_of_philos)
	{
		input -> philos[i].philo_id = i + 1;
		input -> philos[i].input = input;
		input -> philos[i].eat_count = 0;
		input -> philos[i].last_meal = 0;
		input -> philos[i].right_fork = i;
		if (i == input->no_of_philos - 1)
			input -> philos[i].left_fork = 0;
		else
			input -> philos[i].left_fork = i + 1;
		i++;
	}
}
