#include "Room.h"

using namespace std;

bool cstringComparator(const char* a, const char* b) {
  return strcmp(a, b) < 0;
}

Room::Room(const char* roomName, const char* roomDescription) : exits(cstringComparator) {
    strncpy(name, roomName, sizeof(name) - 1);
    strncpy(description, roomDescription, sizeof(description) - 1);
    name[sizeof(name) - 1] = '\0';
    description[sizeof(description) - 1] = '\0';
}

void Room::setExit(const char* direction, Room* room) {
    exits[direction] = room;
}

Room* Room::getExit(const char* direction) {
    if (exits.find(direction) != exits.end())
        return exits[direction];
    return nullptr;
}
//add item functions here - tbd

const char* Room::getName() const {
    return name;
}

const char* Room::getDescription() const {
    return description;
}

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
