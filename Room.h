#ifndef ROOM_H
#define ROOM_H

#include <cstring>
#include <vector>
#include <map>

using namespace std;

class Room {
private:
  char name[80];
  char description[200];
  map<const char*, Room*, bool(*)(const char*, const char*)> exits;
  //tbd vector list of items
  
public:
    Room(const char* name, const char* description);

    void setExit(const char* direction, Room* room);
    Room* getExit(const char* direction);

    //tbd item commands

    const char* getName() const;
    const char* getDescription() const;
    void getExits(char* buffer) const;
};

#endif
  
