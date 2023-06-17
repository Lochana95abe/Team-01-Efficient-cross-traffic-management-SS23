#include <Arduino_FreeRTOS.h>
#include <queue.h>

typedef enum {
  normal = 3,
  paid = 2,
  emergency = 1
} PriorityValue;

typedef enum {
  NORTH,
  EAST,
  WEST,
  SOUTH
} Direction;

typedef enum {
  LEVEL_1 = 1,
  LEVEL_2 = 2,
  LEVEL_3 = 3
} SpeedLevel;

typedef struct {
  int id;
  SpeedLevel speed;
  Direction direction;
  Direction destination;
  PriorityValue priority;
} Vehicle;

void VehicleSpawn() {
  int id = rand() % 50;
  int directionNum = rand() % 4;
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

  int randomPriority = rand() % 3;
  PriorityValue priority;
  switch (randomPriority) {
    case 0:
      priority = emergency;
      break;
    case 1:
      priority = paid;
      break;
    default:
      priority = normal;
      break;
  }

  SpeedLevel speed;
  if ((direction == EAST && directionNum == WEST) || (direction == WEST && directionNum == EAST) ||
      (direction == NORTH && directionNum == SOUTH) || (direction == SOUTH && directionNum == NORTH)) {
    speed = LEVEL_1; // Assign priority level 1 for specified scenarios
  } else {
    switch (priority) {
      case emergency:
        speed = LEVEL_3;
        break;
      case paid:
        speed = LEVEL_2;
        break;
      case normal:
        speed = LEVEL_1;
        break;
    }
  }

  Direction destination;
  switch (direction) {
    case NORTH:
      destination = (Direction)((directionNum + 1) % 4);
      break;
    case EAST:
      destination = (Direction)((directionNum + 1) % 4);
      break;
    case WEST:
      destination = (Direction)((directionNum + 3) % 4);
      break;
    case SOUTH:
      destination = (Direction)((directionNum + 3) % 4);
      break;
  }

  Serial.print("Vehicle spawned with id: ");
  Serial.print(id);
  Serial.print(" || priority value: ");
  Serial.print(priority);
  Serial.print(" || speed level: ");
  Serial.print(speed);
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
}

void vehicleSpawnTask(void *pvParameters) {
  (void) pvParameters; // Unused parameter

  for (;;) {
    VehicleSpawn();
    vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1 second
  }
}

void setup() {
  Serial.begin(9600);

  xTaskCreate(
    vehicleSpawnTask,        // Function that implements the task
    "VehicleSpawnTask",      // Text name for the task
    128,                     // Stack size in bytes
    NULL,                    // Parameter to pass to the task
    1,                       // Task priority
    NULL                     // Task handle (not used)
  );

  vTaskStartScheduler();     // Start the FreeRTOS scheduler
}

void loop() {
  // Empty. The tasks are executed in FreeRTOS scheduler.
}
