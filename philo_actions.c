/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponnusa <tponnusa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 12:56:30 by tponnusa          #+#    #+#             */
/*   Updated: 2023/10/17 15:23:17 by tponnusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_print(t_philo *philo, char *str)
{
	size_t	cur_time;
	int		dead_philo;

	dead_philo = 0;
	while (str[dead_philo])
		dead_philo++;
	pthread_mutex_lock(&philo -> input -> mutex_print);
	if (is_philo_died(philo) == 0 || dead_philo == 4)
	{
		cur_time = get_time_ms() - philo -> input -> start_time;
		printf("%zu Philo %d %s\n", cur_time, philo ->philo_id, str);
		pthread_mutex_unlock(&philo -> input -> mutex_print);
		return ;
	}
	pthread_mutex_unlock(&philo -> input -> mutex_print);
}

int	philo_taken_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->input->forks[philo->right_fork]);
	if (philo->input->fork_at_hand[philo->right_fork] == -1)
	{
		philo->input->fork_at_hand[philo->right_fork] = 0;
		pthread_mutex_unlock(&philo->input->forks[philo->right_fork]);
		pthread_mutex_lock(&philo->input->forks[philo->left_fork]);
		if (philo->input->fork_at_hand[philo->left_fork] == -1)
		{
			philo->input->fork_at_hand[philo->left_fork] = 0;
			pthread_mutex_unlock(&philo->input->forks[philo->left_fork]);
			philo_print(philo, "has taken a fork");
			return (1);
		}
		else
		{
			pthread_mutex_unlock(&philo->input->forks[philo->left_fork]);
			pthread_mutex_lock(&philo->input->forks[philo->right_fork]);
			philo->input->fork_at_hand[philo->right_fork] = -1;
		}
	}
	pthread_mutex_unlock(&philo->input->forks[philo->right_fork]);
	return (0);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->input->forks[philo->right_fork]);
	philo->input->fork_at_hand[philo->right_fork] = -1;
	pthread_mutex_unlock(&philo->input->forks[philo->right_fork]);
	pthread_mutex_lock(&philo->input->forks[philo->left_fork]);
	philo->input->fork_at_hand[philo->left_fork] = -1;
	pthread_mutex_unlock(&philo->input->forks[philo->left_fork]);
}

void	philo_eat_spaghetti(t_philo *philo)
{
	if (is_philo_died(philo))
		return ;
	pthread_mutex_lock(&philo->input->mutex_last_meal);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->input->mutex_last_meal);
	philo_print(philo, "is eating");
	pthread_mutex_lock(&philo -> input -> mutex_eat);
	philo -> eat_count++;
	pthread_mutex_unlock(&philo -> input -> mutex_eat);
	pthread_mutex_lock(&philo->input->sign_mutex[philo->right_fork]);
	philo->input->sign[philo->right_fork] = philo->philo_id;
	pthread_mutex_unlock(&philo->input->sign_mutex[philo->right_fork]);
	pthread_mutex_lock(&philo->input->sign_mutex[philo->left_fork]);
	philo->input->sign[philo->left_fork] = philo->philo_id;
	pthread_mutex_unlock(&philo->input->sign_mutex[philo->left_fork]);
	calculate_usleep(philo -> input ->time_to_eat);
	drop_forks(philo);
	philo_sleep_think(philo);
}

void	philo_sleep_think(t_philo *philo)
{
	if (is_philo_died(philo))
		return ;
	philo_print(philo, "is sleeping");
	calculate_usleep(philo ->input->time_to_sleep);
	if (is_philo_died(philo))
		return ;
	philo_print(philo, "is thinking");
}
