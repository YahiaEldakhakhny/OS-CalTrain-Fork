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
station_init(Station *station)
{
	// Allocate space
	station = malloc(sizeof(Station))
	// At start no train is at the station
	station->is_train = NO_TRAIN_WAITING;
	// At start no one has aquired the lock
	station->lock = LOCK_RELEASED;
	train_available_seats = 0;
	waiting_passengers = 0;
}

// Function called when the train arrives and has opened its doors
// Count is the number of available seats on the train
void
station_load_train(Station *station, int count)
{
	// FILL ME IN
}

void
station_wait_for_train(Station *station)
{
	// FILL ME IN
}

void
station_on_board(Station *station)
{
	// FILL ME IN
}
