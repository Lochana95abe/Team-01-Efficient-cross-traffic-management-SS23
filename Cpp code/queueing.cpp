#include "queueing.hpp"

// Car Class
Car::Car(int id, int speed, int lane, int dest, int enter_time) {
    this->id = id;
    this->lane = lane;
    this->dest = dest;
    this->enter_time = enter_time;
    this->pos = 0;
}

int Car::get_id() {
    return this->id;
}

int Car::get_speed() {
    return this->speed;
}

int Car::get_lane() {
    return this->lane;
}

int Car::get_dest() {
    return this->dest;
}

int Car::get_enter_time() {
    return this->enter_time;
}

int Car::get_pos() {
    return this->pos;
}

void Car::move() {
    this->pos += this->speed;
}

// Lane Class
Lane::Lane(int length) {
    this->length = length;
    this->cars = std::vector<Car*>(length, NULL);
}

int Lane::get_length() {
    return this->length;
}

Car* Lane::get_car(int i) {
    return this->cars[i];
}

void Lane::add_car(Car* car, int pos) {
    this->cars[pos] = car;
}

void Lane::remove_car(int pos) {
    this->cars[pos] = NULL;
}

void Lane::move() {
    for (int i = length - 1; i >= 0; i--) {
        if (cars[i] != NULL) {
            cars[i]->move();
            if (cars[i]->get_pos() >= length) {
                remove_car(i);
            } else {
                int dest = cars[i]->get_dest();
                if (i + 1 < length && cars[i + 1] == NULL) {
                    add_car(cars[i], i + 1);
                    remove_car(i);
                } else if (i + 1 == dest) {
                    remove_car(i);
                }
            }
        }
    }
}

// Intersection Class
Intersection::Intersection() {
    this->car_one = NULL;
    this->r_lane = new Lane(2);
}

Intersection::~Intersection() {
    delete r_lane;
}

Car* Intersection::get_car_one() {
    return this->car_one;
}

void Intersection::set_car_one(Car* car) {
    this->car_one = car;
}

Lane* Intersection::get_r_lane() {
    return this->r_lane;
}

bool Intersection::is_junction_clear() {
    if (car_one != NULL) {
        return false;
    }
    for (int i = 0; i}
    }
}
         
void spawn(int num_cars) {
    for (int i = 0; i < num_cars; i++) {
        // depends on how many cars are on this crossroad
    }

// Car1's function
void carOne() {
    while (true) {
        // If there's no car in queue, wait

        // Get the first car in queue

        // Check if the junction is clear or not

        // Enter junction and make the desired move
    }
}

// Car2's function
void carTwo() {
    while (true) {
        // If there's no car in queue, wait

        // Get the first car in queue

        // Wait until the junction is clear

        // Enter junction and make the desired move

        // Notify that the car has finished

    }
}
