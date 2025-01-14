#ifndef CAR_RENTAL_H
#define CAR_RENTAL_H

#include "car_rental.h"

#define MAX_STRING 50
#define MAX_CARS 100

typedef struct {
    int id;
    char brand[MAX_STRING];
    char user[MAX_STRING];
    char model[MAX_STRING];
    char fuelType[MAX_STRING];
    int seats;
    char transmission[MAX_STRING];
    float rentalPrice;
    int isAvailable;
} Car;

void loadCarsFromFile(Car cars[], int *carCount);
void saveCarsToFile(Car cars[], int carCount);
void displayCars(Car cars[], int carCount);
void addCar(Car cars[], int *carCount);
void modifyCar(Car cars[], int carCount);
void deleteCar(Car cars[], int *carCount);
void searchCars(Car cars[], int carCount);
void sortCars(Car cars[], int carCount);

#endif

