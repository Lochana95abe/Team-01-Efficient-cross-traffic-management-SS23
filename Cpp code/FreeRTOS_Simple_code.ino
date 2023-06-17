#include <Arduino_FreeRTOS.h>
#include <queue.h>

// Constants
const int carSpawnInterval = 2000; // Car spawn interval in milliseconds
const int maxCars = 10; // Maximum number of cars

// Queue to store car IDs
QueueHandle_t carQueue;

// Task handles
TaskHandle_t carSpawnTaskHandle;
TaskHandle_t carMoveTaskHandle;

class Car {
private:
    String id_unique; // unique id of the car, in string. can be randomized
    int lane; // for implementation of north, east, south and west lanes
    int destination; // to which lane the car will travel to
    // we assume there's no U-turn; only 3 choices the car will make
    // e.g. car spawned from West, then it travels to East, South or North only
    int speed; // from 1 to 3 units
    int enter_time; // entrance time

public:
    Car(String id_unique, int lane, int destination, int speed) {
        this->id_unique = id_unique;
        this->lane = lane;
        this->destination = destination;
        this->speed = speed;
        this->enter_time = 0;
    }

    String get_id() {
        return this->id_unique;
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

void carSpawnTask(void *pvParameters) {
    int carId = 1;

    while (1) {
        if (uxQueueSpacesAvailable(carQueue) > 0) {
            Car car("Car" + String(carId), random(0, 4), random(0, 4), random(1, 4)); // Create a new car with random attributes
            xQueueSend(carQueue, &car, portMAX_DELAY); // Add the car ID to the carQueue
            carId++;
        }

        vTaskDelay(carSpawnInterval / portTICK_PERIOD_MS);
    }
}

void carMoveTask(void *pvParameters) {
    Car car("", 0, 0, 0);

    while (1) {
        if (xQueueReceive(carQueue, &car, portMAX_DELAY) == pdTRUE) {
            Serial.print("Car ID: ");
            Serial.print(car.get_id());
            Serial.print(", Lane: ");
            Serial.print(car.get_lane());
            Serial.print(", Destination: ");
            Serial.print(car.get_destination());
            Serial.print(", Speed: ");
            Serial.println(car.get_speed());
        }

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void setup() {
    Serial.begin(9600);
    while (!Serial) continue;

    carQueue = xQueueCreate(maxCars, sizeof(Car)); // Create the carQueue

    // Create carSpawnTask
    xTaskCreate(
        carSpawnTask,                // Function that implements the task
        "CarSpawn",                  // Text name for the task
        configMINIMAL_STACK_SIZE,    // Stack size (in words, not bytes)
        NULL,                        // Parameter to pass to the task
        2,                           // Task priority
        &carSpawnTaskHandle          // Task handle
    );

    // Create carMoveTask
    xTaskCreate(
        carMoveTask,                 // Function that implements the task
        "CarMove",                   // Text name for the task
        configMINIMAL_STACK_SIZE,    // Stack size (in words, not bytes)
        NULL,                        // Parameter to pass to the task
        1,                           // Task priority
        &carMoveTaskHandle           // Task handle
    );

    vTaskStartScheduler(); // Start the FreeRTOS scheduler
}

void loop() {
    // Empty. The tasks are executed in FreeRTOS scheduler.
}
