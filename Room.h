#ifndef ROOM_H
#define ROOM_H

#include <cstring>
#include <vector>
#include <map>
#include "Item.h"

//Room class, represents a location with a name and description
//can hold items and has exits to other rooms
//items can also be dropped or picked up
//created by Tai Wong, November 19th

using namespace std;

//Room class
class Room {
private:
  //name and description of room
  char name[80];
  char description[200];

  //map of exits
  map<const char*, Room*, bool(*)(const char*, const char*)> exits;
  //item vector
  vector<Item> items;
  
public:
  //room constructor
  Room(const char* name, const char* description);

  //exit functions
  void setExit(const char* direction, Room* room);
  Room* getExit(const char* direction);

  //item functions
  void addItem(const Item& item);
  void removeItem(const char* itemName);
  vector<Item>& getItems();

  //room description functions
  const char* getName() const;
  const char* getDescription() const;

  //gives exits
  void getExits(char* buffer) const;
};

#endif
  
