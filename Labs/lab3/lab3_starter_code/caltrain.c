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
	// At start no train is at the station
	station->is_train = NO_TRAIN_WAITING;
	// At start no one has aquired the lock
	station->lock = LOCK_RELEASED;
}

// Function called when the train arrives and has opened its doors
// Count is the number of available seats on the train
void
station_load_train(struct station *station, int count)
{
	// TODO: Enter critical section
	station->train_available_seats = count;
	// TODO: Exit critical sction
	
	/* I can update is_train directly because I assumed 
	there is only one train at a time
	*/
	station->is_train = TRAIN_WAITING;

	// Wait for train to get full or all passengers to board
	while(train_available_seats != 0 && waiting_passengers != 0);

	// Train leaves the station
	station->is_train = NO_TRAIN_WAITING;	
}

void
station_wait_for_train(struct station *station)
{
	// FILL ME IN
}

void
station_on_board(struct station *station)
{
	// FILL ME IN
}
