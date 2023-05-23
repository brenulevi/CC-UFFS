#include "Item.h"

#include<iostream>

Item::Item(int _id) {
    id = _id;
    next = NULL;
    prev = NULL;
}