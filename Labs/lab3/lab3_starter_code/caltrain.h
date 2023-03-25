#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#define LOCK_AQUIRED 1
#define LOCK_RELEASED 0
#define TRAIN_WAITING 1
#define NO_TRAIN_WAITING 0

struct station{
	int is_train; // Determines wether a train is in the station or not
	int train_available_seats;
	int waiting_passengers;
	int lock;
};

void station_init(struct station *station);

void station_load_train(struct station *station, int count);

void station_wait_for_train(struct station *station);

void station_on_board(struct station *station);
