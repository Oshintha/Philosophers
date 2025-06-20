# Philosophers


Represents a single philosopher:

t_philosopher structure
```
typedef struct s_philosopher {
	pthread_t		thread;          // The thread representing the philosopher.
	int				id;              // Unique ID of the philosopher (e.g., 0, 1, 2...).
	size_t			meals_eaten;     // Number of times this philosopher has eaten.
	size_t			last_meal_time;  // Time (in ms) when the philosopher last started eating.
	pthread_mutex_t	*left_fork;      // Pointer to the mutex representing the left fork.
	pthread_mutex_t	*right_fork;     // Pointer to the mutex representing the right fork.
	t_simulation	*sim;            // Pointer to the shared simulation struct.
} t_philosopher;
```

t_simulation structure
Represents the entire simulation setup:
```
typedef struct s_simulation {
	size_t			philo_count;       // Total number of philosophers.
	size_t			time_to_die_ms;    // Time (in ms) a philosopher can live without eating.
	size_t			time_to_eat_ms;    // Time (in ms) it takes to eat.
	size_t			time_to_sleep_ms;  // Time (in ms) to sleep after eating.
	size_t			required_meals;    // Number of meals each philosopher must eat (if limited).
	size_t			satisfied_philos;  // Number of philosophers who have eaten required meals.
	t_philosopher	*philosophers;     // Array of philosopher structs.
	pthread_mutex_t	*forks;            // Array of fork mutexes.
	pthread_mutex_t	print_lock;        // Mutex to synchronize console output.
	int				simulation_over;   // Flag to indicate if the simulation is done.
	size_t			start_time;        // Timestamp (ms) when the simulation started.
} t_simulation;
```
