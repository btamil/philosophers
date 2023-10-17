/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponnusa <tponnusa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:53:57 by tponnusa          #+#    #+#             */
/*   Updated: 2023/10/13 18:28:22 by tponnusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_philo {
	int				philo_id;
	int				right_fork;
	int				left_fork;
	int				eat_count;
	u_int64_t		last_meal;
	struct s_input	*input;
	pthread_t		thread;
}	t_philo;

typedef struct s_input {
	int				no_of_philos;
	size_t			time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat_count;
	int				is_alive;
	size_t			start_time;
	int				*fork_at_hand;
	int				*sign;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*sign_mutex;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_eat;
	pthread_mutex_t	mutex_last_meal;
	pthread_mutex_t	mutex_die;
}	t_input;

int			ft_atoi(char *str);
int			is_valid_input(int ac, char **av);
void		ft_display_message(char *s, int fd);
size_t		get_time_ms(void);
void		calculate_usleep(useconds_t time);
int			is_philo_died(t_philo *philo);
int			check_sign(t_philo *philo);
int			check_death(t_philo *philo);

void		initialize_input(t_input *input, int ac, char **av);
void		initialize_philo(t_input *input);

void		philo_print(t_philo *philo, char *str);
void		philo_eat_spaghetti(t_philo *philo);
int			philo_taken_forks(t_philo *philo);
void		philo_sleep_think(t_philo *philo);

void		exit_error(int err_no);
void		exit_error_free(t_input *input, int err_no);
void		exit_error_free2(t_input *input, int tot_created, int err_no);
void		free_all(t_input *input);
void		destroy_fork_mutexes(t_input *input, int tot_created);
void		destroy_sign_mutexes(t_input *input, int tot_created);

#endif