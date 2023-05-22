#include <iostream>
#include <vector>

class Car {
private:
    string id_unique; // unique id of the car, in string. can be randomized
    int lane; // for implementation of north, east, south and west lanes
    int destination; // to which lane the car will travel to
    // we assume there's no U-turn; only 3 choices the car will make
    // e.g. car spawned from West, then it travels to East, South or North only
    int speed; // from 1 to 3 units
    int enter_time // entrance time

public:
    Car(string id_unique, int id, int lane, int destination, int speed, int enter_time) {
        this->id_unique = id_unique;
        this->id = id;
        this->lane = lane;
        this->destination = destination;
        this->speed = speed;
        this->enter_time
    }

    int get_id() {
        return this->id;
    }

    int get_lane() {
        return this->lane;
    }

    int get_destination() {
        return this->destination;
    }

    int get_speed() {
        return this->speed;
    }
};

class Lane {
private:
    std::vector<Car> cars;

public:
    Lane() {}

    void add_car(Car car) {
        cars.push_back(car);
    }

    void remove_car(int index) {
        cars.erase(cars.begin() + index);
    }

    int get_num_cars() {
        return cars.size();
    }

    Car get_car(int index) {
        return cars[index];
    }
};

class Intersection {
private:
    Lane north_lane;
    Lane east_lane;
    Lane south_lane;
    Lane west_lane;

public:
    Intersection() {}

    void add_car(int lane, Car car) {
        switch (lane) {
            case 0: // North Lane
                north_lane.add_car(car);
                break;
            case 1: // East Lane
                east_lane.add_car(car);
                break;
            case 2: // South Lane
                south_lane.add_car(car);
                break;
            case 3: // West Lane
                west_lane.add_car(car);
                break;
            default:
                break;
        }
    }

    void remove_car(int lane, int index) {
        switch (lane) {
            case 0: // North Lane
                north_lane.remove_car(index);
                break;
            case 1: // East Lane
                east_lane.remove_car(index);
                break;
            case 2: // South Lane
                south_lane.remove_car(index);
                break;
            case 3: // West Lane
                west_lane.remove_car(index);
                break;
            default:
                break;
        }
    }

    int get_num_cars(int lane) {
        switch (lane) {
            case 0: // North Lane
                return north_lane.get_num_cars();
            case 1: // East Lane
                return east_lane.get_num_cars();
            case 2: // South Lane
                return south_lane.get_num_cars();
            case 3: // West Lane
                return west_lane.get_num_cars();
            default:
                return 0;
        }
    }

    Car get_car(int lane, int index) {
        switch (lane) {
            case 0: // North Lane
                return north_lane.get_car(index);
            case 1: // East Lane
                return east_lane.get_car(index);
            case 2: // South Lane
                return south_lane.get_car(index);
            case 3: // West Lane
                return west_lane.get_car(index);
            default:
                return Car(-1, -1, -1, -1);
        }
    }

    void move_cars() {
        for (int lane = 0; lane < 4; lane++) {
            int num_cars = get_num_cars(lane);
            for (int i = 0; i < num_cars; i++) {
                Car car = get_car(lane, i);
                int next_lane = (lane + 1) % 4; // Calculate next lane in round-robin
                remove_car(lane, i);
                add_car(next_lane, car);
            }
        }
    }
};

int main() {
    Intersection intersection;

    // Add cars to lanes
    Car car1(1, 0, 2, 3); // Car ID 1, North Lane, Destination South, Speed 3
    Car car2(2, 1, 3, 2); // Car ID 2, East Lane, Destination West, Speed 2
    Car car3(3, 2, 0, 4); // Car ID 3, South Lane, Destination North, Speed 4
    Car car4(4, 3, 1, 3); // Car ID 4, West Lane, Destination East, Speed 3

    intersection.add_car(car1.get_lane(), car1);
    intersection.add_car(car2.get_lane(), car2);
    intersection.add_car(car3.get_lane(), car3);
    intersection.add_car(car4.get_lane(), car4);

    // Simulate car movement
    int max_iterations = 10;
    for (int i = 0; i < max_iterations; i++) {
        intersection.move_cars();
    }

    // Print the final positions of cars in each lane
    for (int lane = 0; lane < 4; lane++) {
        int num_cars = intersection.get_num_cars(lane);
        std::cout << "Lane " << lane << ": ";
        for (int j = 0; j < num_cars; j++) {
            Car car = intersection.get_car(lane, j);
            std::cout << "Car ID: " << car.get_id() << ", Position: " << j << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
