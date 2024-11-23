#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include "Room.h"
#include "Item.h"

//main code for the Zuul game. This cpp file manages the actual rooms and game that is made using the Room and Item files
//it has 19 rooms and 7 items
//created by Tai Wong, November 21st


using namespace std;

//function prototypes
void displayRoomInfo(Room* currentRoom);
bool hasAllItems(const vector<Item>& inventory);

int main() {
  //create all rooms

  vector<Room*> rooms; //vector to store all room pointers

  Room* outside = new Room("outside", "outside the front side of sunset high school");
  Room* cafeteria = new Room("cafeteria", "in the cafeteria");
  Room* physics = new Room("physics class", "in the ib physics class");
  Room* java = new Room("java class", "in java class");
  Room* math = new Room("math class", "in math class");
  Room* hhall = new Room("h hall", "in h hall");
  Room* onehall = new Room("1 hall", "in 1 hall");
  Room* mainhall = new Room("main hall", "in the main hall");
  Room* dhall = new Room("d hall", "in d hall");
  Room* sportssci = new Room("sports science class", "in sports science class");
  Room* bhall = new Room("b hall", "in b hall");
  Room* litcomp = new Room("lit and comp class", "in lit and comp class");
  Room* ahall = new Room("a hall", "in a hall");
  Room* mainoffice = new Room("main office", "in the main office");
  Room* parking = new Room("parking lot", "in the parking lot");
  Room* busstop = new Room("bus stop", "at the bus stop");
  Room* crosswalk = new Room("crosswalk", "at the crosswalk");
  Room* bank = new Room("bank", "at the bank");
  Room* petershouse = new Room("peter's house", "at peter's house");

  //add all rooms to the vector
  rooms.push_back(outside);
  rooms.push_back(cafeteria);
  rooms.push_back(physics);
  rooms.push_back(java);
  rooms.push_back(math);
  rooms.push_back(hhall);
  rooms.push_back(onehall);
  rooms.push_back(mainhall);
  rooms.push_back(dhall);
  rooms.push_back(sportssci);
  rooms.push_back(bhall);
  rooms.push_back(litcomp);
  rooms.push_back(ahall);
  rooms.push_back(mainoffice);
  rooms.push_back(parking);
  rooms.push_back(busstop);
  rooms.push_back(crosswalk);
  rooms.push_back(bank);
  rooms.push_back(petershouse);
  
  //link rooms with exits
  
  outside->setExit("north", parking);
  parking->setExit("south", outside);
  parking->setExit("east", crosswalk);
  crosswalk->setExit("west", parking);
  crosswalk->setExit("north", bank);
  bank->setExit("south", crosswalk);
  parking->setExit("west", busstop);
  busstop->setExit("east", parking);
  busstop->setExit("north", petershouse);
  petershouse->setExit("south", busstop);
  outside->setExit("south", mainoffice);
  mainoffice->setExit("north", outside);
  mainoffice->setExit("south", mainhall);
  mainhall->setExit("north", mainoffice);
  mainhall->setExit("south", cafeteria);
  cafeteria->setExit("north", mainhall);
  mainhall->setExit("west", dhall);
  dhall->setExit("east", mainhall);
  dhall->setExit("south", physics);
  physics->setExit("north", dhall);
  dhall->setExit("west", sportssci);
  sportssci->setExit("east", dhall);
  dhall->setExit("north", bhall);
  bhall->setExit("south", dhall);
  bhall->setExit("west", litcomp);
  litcomp->setExit("east", bhall);
  bhall->setExit("north", ahall);
  ahall->setExit("south", bhall);
  mainhall->setExit("east", onehall);
  onehall->setExit("west", mainhall);
  onehall->setExit("south", java);
  java->setExit("north", onehall);
  onehall->setExit("east", hhall);
  hhall->setExit("west", onehall);
  hhall->setExit("south", math);
  math->setExit("north", hhall);

    
  //Add items to rooms

  math->addItem(Item("math_homework"));
  physics->addItem(Item("physics_homework"));
  java->addItem(Item("java_project_homework"));
  sportssci->addItem(Item("sports_science_test"));
  litcomp->addItem(Item("lit_and_comp_essay"));
  cafeteria->addItem(Item("lunch"));
  bank->addItem(Item("money"));

  Room* currentRoom = outside;
  vector<Item> inventory;
  bool gameRunning = true;

  cout << "welcome to the generic adventure game that is really fun!\n";
  cout << "collect all the items and deliver them to peter's house to win.\n";

  //runs the game until the user wins
  while (gameRunning) {

    displayRoomInfo(currentRoom);

    cout << "Enter a command (go, pickup, drop, inventory, quit): ";

    char command[100];

    cin.getline(command, sizeof(command));
    //go command
    if (strncmp(command, "go ", 3) == 0) {

      const char* direction = command + 3;
      Room* nextRoom = currentRoom->getExit(direction);
      
      if (nextRoom) {
	//changes current room
	currentRoom = nextRoom;
	//checks if user wins game
        if (currentRoom == petershouse && hasAllItems(inventory)) {
	  cout << "congratulations! you delivered all the items to peter's house.\n";
          cout << "you win the game!\n";

          gameRunning = false;
	}
      } else {
	cout << "you can't go that way.\n";
      }
      //pickup item command
    } else if (strncmp(command, "pickup ", 7) == 0) {
      
      const char* itemName = command + 7;
      auto& items = currentRoom->getItems();
      //returms current items in room

      //pickup code
      auto it = find_if(items.begin(), items.end(), [itemName](const Item& i) { return strcmp(i.getName(), itemName) == 0; });
      if (it != items.end()) {
	inventory.push_back(*it);
        currentRoom->removeItem(itemName);
        cout << "picked up " << itemName << ".\n";
      } else {
	cout << "item not found in the room.\n";
      }

      //drop item code
    } else if (strncmp(command, "drop ", 5) == 0) {

      const char* itemName = command + 5;

      //code to find item and drop it
      auto it = find_if(inventory.begin(), inventory.end(), [itemName](const Item& i) { return strcmp(i.getName(), itemName) == 0; });
      if (it != inventory.end()) {
	currentRoom->addItem(*it);
        inventory.erase(it);
        cout << "dropped " << itemName << ".\n";
      } else {
	cout << "you don't have that item.\n";
      }
      
      //inventory code
    } else if (strcmp(command, "inventory") == 0) {

      //just lists out the vector of items you have
      cout << "you are carrying: ";
      for (const auto& item : inventory) {
	cout << item.getName() << " ";
      }
      cout << "\n";

      //quit code
    } else if (strcmp(command, "quit") == 0) {
      
      cout << "goodbye!\n";
      gameRunning = false;
    } else {
      cout << "unknown command.\n";
    }
  }

  //cleanup code
  for (Room* room : rooms) {
    delete room;
  }

  return 0;
}

//function definitions

//code to print out room info
void displayRoomInfo(Room* currentRoom) {
  
  //tells user the current room information and exits
  cout << "\nYou are in: " << currentRoom->getName() << "\n";
  cout << currentRoom->getDescription() << "\n";
    
  char exits[100];

  currentRoom->getExits(exits);
  cout << "Exits: " << exits << "\n";
  
  //returns current room items
  auto& items = currentRoom->getItems();

  if (!items.empty()) {
    cout << "Items in the room: ";
    for (const auto& item : items) {
      cout << item.getName() << " ";
    }
    cout << "\n";
  } else {
    cout << "There are no items in the room.\n";
  }
}

//code to check if user has all items to win the game
bool hasAllItems(const vector<Item>& inventory) {
  //require items list

  const char* requiredItems[] = {"math_homework", "physics_homework", "java_project_homework",
                                   "sports_science_test", "lit_and_comp_essay", "lunch", "money"};

  //loops and checks if inventory contains each item
  for (const char* item : requiredItems) {
    auto it = find_if(inventory.begin(), inventory.end(), [item](const Item& i) { return strcmp(i.getName(), item) == 0; });

    if (it == inventory.end()) {
      return false;
    }
  }
  return true;
}
