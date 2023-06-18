#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

typedef enum {
  normal = 1,
  priority = 2
} PriorityValue;

typedef enum {
  NORTH,
  EAST,
  WEST,
  SOUTH
} Direction;

typedef struct {
  int id;
  Direction direction;
  Direction destination;
  PriorityValue priority;
} Vehicle;

void VehicleSpawn(void *pvParameters) {
  (void)pvParameters;

  for (;;) {
    int id = random(100);
    int directionNum = random(4);
    Direction direction;
    switch (directionNum) {
      case 0:
        direction = NORTH;
        break;
      case 1:
        direction = EAST;
        break;
      case 2:
        direction = WEST;
        break;
      case 3:
        direction = SOUTH;
        break;
    }

    Direction destination;
    PriorityValue priority = normal;

    if ((direction == SOUTH && directionNum == EAST) ||
        (direction == EAST && directionNum == NORTH) ||
        (direction == NORTH && directionNum == WEST) ||
        (direction == WEST && directionNum == SOUTH) ||
        (direction == WEST && directionNum == EAST) ||
        (direction == EAST && directionNum == SOUTH)) {
      destination = (Direction)((directionNum + 1) % 4);
      priority = priority;
    } else {
      destination = (Direction)((directionNum + 2) % 4);
    }

    Serial.print("Vehicle spawned with id: ");
    Serial.print(id);

    if ((direction == SOUTH && destination == EAST) ||
        (direction == EAST && destination == NORTH) ||
        (direction == NORTH && destination == WEST) ||
        (direction == WEST && destination == SOUTH) ||
        (direction == WEST && destination == EAST) ||
        (direction == EAST && destination == SOUTH)) {
      Serial.print(" || Move with priority: ");
      switch (direction) {
        case SOUTH:
          Serial.print("South to East");
          break;
        case EAST:
          Serial.print("East to North");
          break;
        case NORTH:
          Serial.print("North to West");
          break;
        case WEST:
          Serial.print("West to South");
          break;
      }
    }

    Serial.print(" || from ");
    switch (direction) {
      case NORTH:
        Serial.print("North");
        break;
      case EAST:
        Serial.print("East");
        break;
      case WEST:
        Serial.print("West");
        break;
      case SOUTH:
        Serial.print("South");
        break;
    }

    Serial.print(" to the destination ");
    switch (destination) {
      case NORTH:
        Serial.println("North");
        break;
      case EAST:
        Serial.println("East");
        break;
      case WEST:
        Serial.println("West");
        break;
      case SOUTH:
        Serial.println("South");
        break;
    }

    vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1 second
  }
}

void setup() {
  Serial.begin(9600);

  xTaskCreate(
    VehicleSpawn,             // Function that implements the task
    "VehicleSpawnTask",       // Text name for the task
    128,                      // Stack size in bytes
    NULL,                     // Parameter to pass to the task
    1,                        // Task priority
    NULL                      // Task handle (not used)
  );

  vTaskStartScheduler();      // Start the FreeRTOS scheduler
}

void loop() {
  // Empty. The tasks are executed in FreeRTOS scheduler.
}
