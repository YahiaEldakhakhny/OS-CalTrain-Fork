#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

struct station{
	int train_available_seats;
	int waiting_passengers;
	int boarded_passengers; // number of passengers who have boarded the train
	pthread_mutex_t seats_mutex;
	pthread_cond_t train_arrived_cond;
	pthread_cond_t passenger_aboard_cond;
};

void station_init(struct station *station);

void station_load_train(struct station *station, int count);

void station_wait_for_train(struct station *station);

void station_on_board(struct station *station);
