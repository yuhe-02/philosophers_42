
#include "philo.h"

//  wrond case
// void *routine(void *arg)
// {
// 	int *n = (int *)arg;

// 	(*n)++;
// 	return NULL;
// }

// int main(void)
// {
// 	pthread_t	threads[100000];

// 	int n = 0;

// 	for (int i = 0; i < 100000; i++)
// 		pthread_create(&threads[i], NULL, routine, &n);

// 	for (int i = 0; i < 100000; i++)
// 		pthread_join(threads[i], NULL);

// 	printf("n = %d\n", n);
// 	return 0;
// }

// collect case
typedef struct routine_arg {
	int				n;
	pthread_mutex_t mutex;
}	routine_arg;

void *routine(void *arg)
{
	routine_arg	*r_arg = (routine_arg *)arg;

	pthread_mutex_lock(&r_arg->mutex);
	r_arg->n++;
	pthread_mutex_unlock(&r_arg->mutex);

	return NULL;
}

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

int main(void)
{
	pthread_t	threads[100000];
	routine_arg	arg;
	long long	first_timestamp;

	arg.n = 0;
	pthread_mutex_init(&arg.mutex, NULL);

	for (int i = 0; i < 100000; i++)
		pthread_create(&threads[i], NULL, routine, &arg);

	for (int i = 0; i < 100000; i++)
		pthread_join(threads[i], NULL);

	printf("n = %d\n", arg.n);
	printf("%lld\n", timestamp());
	printf("%d\n", True);


	pthread_mutex_destroy(&arg.mutex);
	return 0;
}