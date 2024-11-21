#include "Room.h"

//Room.cpp file for the Room Class
//Created by Tai Wong, November 19th

using namespace std;

//cstring compare function for exits map
bool cstringComparator(const char* a, const char* b) {
  return strcmp(a, b) < 0;
}

//item comparator 
struct ItemComparator {
  const char* itemName;

  ItemComparator(const char* itemName) : itemName(itemName) {}

  bool operator()(const Item& item) const {
    return strcmp(item.getName(), itemName) == 0;
  }
};

//room constructor
Room::Room(const char* roomName, const char* roomDescription) : exits(cstringComparator) {

  //copy name and description
  strncpy(name, roomName, sizeof(name) - 1);
  strncpy(description, roomDescription, sizeof(description) - 1);
  name[sizeof(name) - 1] = '\0';
  description[sizeof(description) - 1] = '\0';
}

//sets room exit
void Room::setExit(const char* direction, Room* room) {
  exits[direction] = room;
}
//gets connected rooms in specified direction
Room* Room::getExit(const char* direction) {
  if (exits.find(direction) != exits.end())
    return exits[direction];
  return nullptr;
}

//adds an item to the room
void Room::addItem(const Item& item) {
  items.push_back(item);
}

//removes an item from the room by name using the item comparator
void Room::removeItem(const char* itemName) {
  items.erase(std::remove_if(items.begin(), items.end(), ItemComparator(itemName)), items.end());
}

//returns vector of items
vector<Item>& Room::getItems() {
  return items;
}

//returns room name
const char* Room::getName() const {
  return name;
}

//returns room description
const char* Room::getDescription() const {
  return description;
}

//returns exits
void Room::getExits(char* buffer) const {
  buffer[0] = '\0';
  for (const auto& exit : exits) {
    strcat(buffer, exit.first);
    strcat(buffer, " ");
  }
  if (buffer[0] == '\0') {
    strcat(buffer, "None");
  }
}
