#ifndef ITEM_H
#define ITEM_H

//header file for the Item class
//created by Tai Wong, November 21st

#include <cstring>

//class to store items
class Item {
private:
  //name of the item
  char name[80]; 

public:
  //constructor
  Item(const char* itemName);

  // getter for the name
  const char* getName() const;
};

#endif
