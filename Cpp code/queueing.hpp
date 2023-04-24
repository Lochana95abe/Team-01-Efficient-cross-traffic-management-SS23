#ifndef QUEUEING_HPP
#define QUEUEING_HPP

#include <iostream>
#include <queue>
#include <chrono>
#include <thread>

class Car {
public:
    Car(int id, int lane, int speed, int position, int destination);
    int id;
    int lane;
    int speed;
    int position;
    int destination;
    int distance_to_obstacle;
    int distance_to_junction;
    int time_to_clear_junction;
    bool operator<(const Car& other) const;
    void move();
    void Request_to_enter();
    void exit_street();
    void enter_junction();
    void exit_junction();
    void street_continue();
    void priority_check();
    void spawn();
};

class Road {
public:
    Road(int num_lanes, int road_length, int junction_pos);
    int num_lanes;
    int road_length;
    int junction_pos;
    std::vector<std::queue<Car>> lanes;
    std::vector<int> junction_lanes;
    std::vector<std::vector<int>> obstacle_positions;
    void move_cars();
    void print_road();
};

#endif
