#pragma once

#include "Item.h"

class List {
public:
    Item* first;
    Item* last;

    int size;

    List();

    Item* searchItem(int id);

    void insert(Item* item);

    void remove(int id);

    void print();
};