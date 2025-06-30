# Philosophers


Represents a single philosopher:

t_philosopher structure
```
typedef struct s_philosopher
{
	pthread_t		thread;             // Thread representing the philosopher
	int				id;                 // Philosopher ID (1-based)
	size_t			meals_eaten;        // How many times this philosopher has eaten
	size_t			last_meal_time;     // Timestamp of last meal in ms
	size_t			left_fork_index;    // Index of the left fork in the forks array
	size_t			right_fork_index;   // Index of the right fork in the forks array
	t_simulation	*sim;               // Pointer to the shared simulation data
}	t_philosopher;
```

t_simulation structure
Represents the entire simulation setup:
```
typedef struct s_simulation
{
	size_t			philo_count;        // Total number of philosophers
	size_t			time_to_die_ms;     // Max time a philosopher can go without eating
	size_t			time_to_eat_ms;     // Duration of eating
	size_t			time_to_sleep_ms;   // Duration of sleeping
	size_t			required_meals;     // Optional limit per philosopher
	size_t			satisfied_philos;   // Number of philosophers who met the eating goal
	t_philosopher	*philosophers;      // Array of all philosophers
	pthread_mutex_t	*forks;             // Array of fork mutexes
	pthread_mutex_t	print_lock;         // Mutex to prevent mixed output
	int				simulation_over;    // Flag to indicate simulation has ended
	size_t			start_time;         // Timestamp of simulation start
}	t_simulation;
```
