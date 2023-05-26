#include <iostream>
#include <cstdlib>   // to genaratevrandom numbers

using namespace std;

enum PriorityValue { // to represent the priority levels
  normal = 3,  //priority level 03: normal vehicles, first come first serve
  paid = 2,    // priority level 02: paid for priority vehicles
  emergency = 1 // priority level 01: emergency vehicles, ambulance, police etc..
};

enum Direction {  //spawn directions
  NORTH,
  EAST,
  WEST,
  SOUTH
};

struct Vehicle { // custom representation of the vehicle's data set
  int id;
  PriorityValue priority;
  Direction direction;
  Direction destination;
};

void VehicleSpawn() {
 int id = rand() % 1000; // to ensure better randomality

  int RandomPriority = rand() % 3;  // Generate a random priority level for the vehicle
  PriorityValue priority;
  switch (RandomPriority) {
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

  int directionNum = rand() % 4; // Generate a random direction for the vehicle
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
    default:
      direction = SOUTH;
      break;
  }

  
  Direction destination;  // randomly select spawn direction to destination direction
  switch (direction) {
    case NORTH:
      destination = SOUTH;
      break;
    case EAST:
      destination = WEST;
      break;
    case WEST:
      destination = EAST;
      break;
    default:
      destination = NORTH;
      break;
  }

  cout << "Vehicle spawned id:" << id << " priority value:" << priority << " from ";  // Spawn the vehicle in the right lane of the road
  switch (direction) {
    case NORTH:
      cout << "North";
      break;
    case EAST:
      cout << "East";
      break;
    case WEST:
      cout << "West";
      break;
    default:
      cout << "South";
      break;
  }
  cout << " to the destination ";
  switch (destination) {
    case NORTH:
      cout << "North";
      break;
    case EAST:
      cout << "East";
      break;
    case WEST:
      cout << "West";
      break;
    default:
      cout << "South";
      break;
  }
  cout << " on the right-lane." << endl;
}

int main() {
  
  srand(time(0)); //random number generator
 
  for (int i = 0; i < 100; i++) { // Spawn vehicles 
    VehicleSpawn();
  }

  return 0;
}