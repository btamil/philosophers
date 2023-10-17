/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponnusa <tponnusa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:53:30 by tponnusa          #+#    #+#             */
/*   Updated: 2023/10/17 11:48:33 by tponnusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_input *input)
{
	if (input -> philos)
		free(input -> philos);
	destroy_fork_mutexes(input, input -> no_of_philos);
	destroy_sign_mutexes(input, input -> no_of_philos);
	if (input -> forks)
		free(input -> forks);
	if (input -> sign_mutex)
		free(input -> sign_mutex);
	if (input -> fork_at_hand)
		free(input -> fork_at_hand);
	if (input -> sign)
		free(input -> sign);
	pthread_mutex_destroy(&input -> mutex_print);
	pthread_mutex_destroy(&input -> mutex_eat);
	pthread_mutex_destroy(&input -> mutex_last_meal);
	pthread_mutex_destroy(&input -> mutex_die);
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	pthread_mutex_lock(&philo->input->mutex_last_meal);
	philo -> last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->input->mutex_last_meal);
	while (1)
	{
		if (is_philo_died(philo)
			|| philo->eat_count == philo->input->max_eat_count)
			return (NULL);
		if (!is_philo_died(philo))
		{
			if (check_death(philo) == 0 && check_sign(philo) == 0
				&& philo_taken_forks(philo))
			{
				philo_eat_spaghetti(philo);
			}
			usleep(100);
		}
	}
	return (NULL);
}

void	create_philos(t_input *input)
{
	int	i;

	i = 0;
	while (i < input -> no_of_philos)
	{
		if (pthread_create(&input -> philos[i].thread, NULL,
				philo_routine, &input -> philos[i]) != 0)
			exit_error_free(input, 1);
		i++;
	}
	i = 0;
	while (i < input -> no_of_philos)
	{
		if (pthread_join(input -> philos[i].thread, NULL) != 0)
			exit_error_free(input, 2);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_input	input;

	if (ac < 5 || ac > 6)
		exit_error(1);
	if (!is_valid_input(ac, av))
		exit_error(2);
	initialize_input(&input, ac, av);
	initialize_philo(&input);
	create_philos(&input);
	free_all(&input);
	return (EXIT_SUCCESS);
}
