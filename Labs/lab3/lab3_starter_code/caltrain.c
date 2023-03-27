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

	// Initialise mutex
	pthread_mutex_init(&(station->seats_mutex), NULL);

	// Initialise condition variables
	pthread_cond_init(&(station->train_arrived_cond), NULL);
	pthread_cond_init(&(station->passenger_aboard_cond), NULL);

	// Initial values
	station->train_available_seats = 0;	
	station->waiting_passengers = 0;	
	station->boarded_passengers = 0;
}

// Function called when the train arrives and has opened its doors
// Count is the number of available seats on the train
void
station_load_train(struct station *station, int count)
{
	// Enter critical section
	pthread_mutex_lock(&(station->seats_mutex));
	station->train_available_seats = count;
	pthread_mutex_unlock(&(station->seats_mutex));	
	
	// Broadcast that the train has entered the station
	pthread_cond_broadcast(&(station->train_arrived_cond));

	// Wait for train to get full or all passengers to board
	pthread_mutex_lock(&(station->seats_mutex));	
	while(station->waiting_passengers > 0 && count > station->boarded_passengers){
		pthread_cond_wait(&(station->passenger_aboard_cond), &(station->seats_mutex));		
	}
	pthread_mutex_unlock(&(station->seats_mutex));

	// Reset variables for next train
	station->boarded_passengers = 0;
	station->train_available_seats = 0;
	
	// Train leaves the station
}

void
station_wait_for_train(struct station *station)
{
	// Update number of waiting passengers
	pthread_mutex_lock(&(station->seats_mutex));
	(station->waiting_passengers)++;

	// Wait for train to arrive	
	while(station->train_available_seats < 1){
		pthread_cond_wait(&(station->train_arrived_cond), &(station->seats_mutex));		
	}
	
	// If passenger has place on the train reserve a place for them
	station->train_available_seats--;
	pthread_mutex_unlock(&(station->seats_mutex));
}

void
station_on_board(struct station *station)
{
	// Let passenger aboard the train
	pthread_mutex_lock(&(station->seats_mutex));
	(station->waiting_passengers)--;
	(station->boarded_passengers)++;
	pthread_mutex_unlock(&(station->seats_mutex));
	pthread_cond_signal(&(station->passenger_aboard_cond));
}
