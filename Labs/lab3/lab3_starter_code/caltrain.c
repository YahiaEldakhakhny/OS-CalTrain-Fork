/*
This code is the work of
Yahia Walid Mohamad Eldakhakhny		19016891
Detailed project description is at:
https://github.com/YahiaEldakhakhny/OS-CalTrain-Fork/tree/master/Labs/lab3
*/

#include <pthread.h>
#include "caltrain.h"

// "Station" is the same as "struct station" I just used typedef to make my life easier

void
station_init(struct station *station)
{
	// Allocate space
	station = malloc(sizeof(struct station));

	// Initialise mutex
	pthread_mutex_init(&(station->seats_mutex), NULL);

	// Initialise condition variables
	pthread_cond_init(&(station->train_arrived_cond), NULL);
	pthread_cond_init(&(station->train_leave_cond), NULL);

}

// Function called when the train arrives and has opened its doors
// Count is the number of available seats on the train
void
station_load_train(struct station *station, int count)
{
	
	// Enter critical section
	pthread_mutex_lock(&(station->seats_mutex));
	if(station->waiting_passengers == 0){
		pthread_mutex_unlock(&(station->seats_mutex));
		return;
	}
	station->train_available_seats = count;
	// Exit critical section
	pthread_mutex_unlock(&(station->seats_mutex));	
	
	// Signal that the train has entered the station
	pthread_cond_broadcast(&(station->train_arrived_cond));
	// Wait for train to get full or all passengers to board
	pthread_cond_wait(&(station->train_leave_cond), &(station->seats_mutex));

	// Train leaves the station
}

void
station_wait_for_train(struct station *station)
{
	// Update number of waiting passengers
	pthread_mutex_lock(&(station->seats_mutex));
	(station->waiting_passengers)++;
	pthread_mutex_unlock(&(station->seats_mutex));

	// Wait for train to arrive	
	pthread_cond_wait(&(station->train_arrived_cond), &(station->seats_mutex));
}

void
station_on_board(struct station *station)
{
	// Let passenger on train
	pthread_mutex_lock(&(station->seats_mutex));
	(station->waiting_passengers)--;
	(station->train_available_seats)--;
	if(station->waiting_passengers == 0 || station->train_available_seats == 0){
		pthread_cond_signal(&(station->train_leave_cond));
	}
	pthread_mutex_unlock(&(station->seats_mutex));

}
