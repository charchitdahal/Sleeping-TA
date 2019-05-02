/**
 * General structure of a student.
 *
 */

#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "ta.h"

void *student_loop(void *param)
{
	int number = *((int *)param);
	int sleep_time;
	int helped = 0;
	int waiting = 0;

	printf("I am student %d\n", number);

	srandom((unsigned)time(NULL));
	sleep_time = (int)((random() % MAX_SLEEP_TIME) + 1);
	programming(sleep_time);

	while(helped == 0){
		//Check to see if the TA is serving another student
		printf("Student %i: I'll check the room for help!\n", number);
		
		//Try to acquire a lock on the chair in the room
		if(pthread_mutex_trylock(&mutex_lock) == 0){
			
			//If the student was holding a chair in the hallway, release the chair
			if (waiting == 1){
				sem_post(&students_sem);
			}
			
			//Wake up the TA and get help
			sem_post(&ta_sem);
			printf("Student %i: Hi TA, I need to be assisted!\n", number);
			
			//Indicate if the student received help so that the thread will terminate
			helped = 1;
			
			//Give the student the time they need
			programming(sleep_time);
			
			//Release the lock when the student is done with the TA
			printf("Student %i: Thanks for the help!\n", number);
			pthread_mutex_unlock(&mutex_lock);
		}
		//If the TA is serving another student, look for a chair in the hallway
		else{
			//If the student hasn't checked for a seat yet, try to grab a chair
			if (waiting == 0){
				//Indicates if the student has already acquired a chair
				waiting = 1;
				
				//Grab a chair. Block if no chairs available
				sem_wait(&students_sem);
				printf("Student %i: I'll be out in the hallway!\n", number);
			}
			
			//Sleep the thread to show that the student is programming while waiting to check the TA again.
			printf("Student %i: The TA is busy, I'll sit here and program.\n", number);
			programming(sleep_time);
		}
	}
	pthread_exit(0);
}

