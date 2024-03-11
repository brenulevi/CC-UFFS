#pragma once

class Item {
public:
    int id;
    Item* next;
    Item* prev;

    Item(int _id);
};