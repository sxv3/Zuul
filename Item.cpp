#include "Item.h"

//Item.cpp for the Item class
//Created by Tai Wong, November 21st.

//constructor
Item::Item(const char* itemName) {
  strncpy(name, itemName, sizeof(name) - 1);
  name[sizeof(name) - 1] = '\0'; // ensures null termination
}
//getter
const char* Item::getName() const {
  return name;
}
