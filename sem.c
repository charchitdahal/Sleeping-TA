/**
 * Demonstration of POSIX unnamed semaphores
 *
 * Note - these will not work on OS X systems.
 *
 * gcc -lpthread sem.c
 */

#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>

int main(void)
{
	
	/* semaphores and mutex lock */
	pthread_mutex_t 	mutex_lock;

	/* semaphore declarations */
	sem_t 			sem;
	sem_t			students_sem;
	sem_t			ta_sem;

	if (sem_init(&sem,0,1) == -1)
		printf("%s\n",strerror(errno));

	if (sem_wait(&sem) != 0)
		printf("%s\n",strerror(errno));

	printf("Critical Section\n");

	if (sem_post(&sem) != 0)
		printf("%s\n",strerror(errno));
	
	printf("Non-Critical Section\n");

	if (sem_destroy(&sem) != 0)
		printf("%s\n",strerror(errno));

	return 0;
}	


