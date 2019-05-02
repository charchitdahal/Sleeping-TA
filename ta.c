/**
 * General structure of the teaching assistant.
 * @author Charhit Dahal
 */

#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "ta.h"

void *ta_loop(void *param)
{
	printf("I am the TA\n");
//Mutex lock
	pthread_mutex_init(&mutex_lock, NULL);
	
	//hallway chairs semaphore
	sem_init(&students_sem, 0, NUM_OF_SEATS);
	
	//ta semaphore
	sem_init(&ta_sem, 0, 0);
	
	//Indicates how many students were served
	int stu_served = 0;

	//Insert time into rand for seeding
	srand(time(NULL));
	
	while(stu_served < NUM_OF_STUDENTS){
		//Generate random number to sleep
		int sleep_time = (int)((random() % MAX_SLEEP_TIME) + 1);

		//Make the TA sleep until a student asks for help
		// This blocks the process until another process posts
		sem_wait(&ta_sem);

		//Indicate that the TA is ready to serve the student
		printf("TA: Hi Student, how can I assist you?\n");
		//Increase number of students served
		stu_served += 1;
	
	}
	
	//Exit the thread
	pthread_exit(0);

}

