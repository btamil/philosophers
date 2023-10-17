/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponnusa <tponnusa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:31:59 by tponnusa          #+#    #+#             */
/*   Updated: 2023/10/13 14:03:45 by tponnusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_philo_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->input->mutex_die);
	if (philo->input->is_alive == 0)
	{
		pthread_mutex_unlock(&philo->input->mutex_die);
		return (1);
	}
	pthread_mutex_unlock(&philo->input->mutex_die);
	return (0);
}

int	check_sign(t_philo *philo)
{
	pthread_mutex_lock(&philo->input->sign_mutex[philo->right_fork]);
	if (philo->input->sign[philo->right_fork] != philo->philo_id)
	{
		pthread_mutex_unlock(&philo->input->sign_mutex[philo->right_fork]);
		pthread_mutex_lock(&philo->input->sign_mutex[philo->left_fork]);
		if (philo->input->sign[philo->left_fork] != philo->philo_id)
		{
			pthread_mutex_unlock(&philo->input->sign_mutex[philo->left_fork]);
			return (0);
		}
		else
			pthread_mutex_unlock(&philo->input->sign_mutex[philo->left_fork]);
	}
	else
		pthread_mutex_unlock(&philo->input->sign_mutex[philo->right_fork]);
	return (1);
}

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->input->mutex_last_meal);
	if ((get_time_ms() - philo->last_meal) >= philo->input->time_to_die)
	{
		pthread_mutex_unlock(&philo->input->mutex_last_meal);
		pthread_mutex_lock(&philo->input->mutex_die);
		if (philo->input->is_alive == 1)
		{
			philo->input->is_alive = 0;
			pthread_mutex_unlock(&philo->input->mutex_die);
			philo_print(philo, "died");
			return (1);
		}
		pthread_mutex_unlock(&philo->input->mutex_die);
	}
	else
		pthread_mutex_unlock(&philo->input->mutex_last_meal);
	return (0);
}
