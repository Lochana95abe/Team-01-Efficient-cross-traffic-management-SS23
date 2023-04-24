#include "queueing.hpp"

// Car Class
Car::Car(int id, int speed, int lane, int dest, int enter_time) {
    this->id = id;
    this->speed = speed;
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

// Street Class
Street::Street(int length, int num_lanes) {
    this->length = length;
    this->num_lanes = num_lanes;
    this->lanes = new Lane*[num_lanes];
    for (int i = 0; i < num_lanes; i++) {
        this->lanes[i] = new Lane(length);
    }
}

Street::~Street() {
    for (int i = 0; i < num_lanes; i++) {
        delete lanes[i];
    }
    delete[] lanes;
}

int Street::get_length() {
    return this->length;
}

int Street::get_num_lanes() {
    return this->num_lanes;
}

Lane* Street::get_lane(int i) {
    return this->lanes[i];
}

void Street::move() {
    for (int i = 0; i < num_lanes; i++) {
        lanes[i]->move();
    }
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

// Car1's function
void carOne(queue<Car>& q1, std::mutex& mtx, std::condition_variable& cv) {
    while (true) {
        // If there's no car in queue, wait
        std::unique_lock<std::mutex> lck(mtx);
        cv.wait(lck, [&q1] { return !q1.empty(); });

        // Get the first car in queue
        Car car = q1.front();
        q1.pop();
        lck.unlock();

        // Check if the junction is clear or not
        bool clear = false;
        while (!clear) {
            std::lock_guard<std::mutex> lck(mtx);
            clear = priority_check(car, q1);
        }

        // Enter junction and make the desired move
        enter_junction(car);
        move(car, rLane);
        exit_junction(car);
        move(car, rLane);
        exit_street(car);

        // Notify that the car has finished
        {
            std::lock_guard<std::mutex> lck(mtx);
            finished_cars++;
            if (finished_cars == TOTAL_CARS) {
                cv.notify_all();
                break;
            }
        }
    }
}

// Car2's function
void carTwo(queue<Car>& q2, std::mutex& mtx, std::condition_variable& cv) {
    while (true) {
        // If there's no car in queue, wait
        std::unique_lock<std::mutex> lck(mtx);
        cv.wait(lck, [&q2] { return !q2.empty(); });

        // Get the first car in queue
        Car car = q2.front();
        q2.pop();
        lck.unlock();

        // Wait until the junction is clear
        {
            std::lock_guard<std::mutex> lck(mtx);
            while (!priority_check(car, q1)) {}
        }

        // Enter junction and make the desired move
        enter_junction(car);
        move(car, lLane);
        exit_junction(car);
        move(car, lLane);
        exit_street(car);

        // Notify that the car has finished
        {
            std::lock_guard<std::mutex> lck(mtx);
            finished_cars++;
            if (finished_cars == TOTAL_CARS) {
                cv.notify_all();
                break;
            }
        }
    }
}
