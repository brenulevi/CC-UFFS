#include "List.h"

#include<iostream>

int main() {
    List myList = List();

    Item item1 = Item(0);
    Item item2 = Item(1);
    Item item3 = Item(2);

    myList.insert(&item2);
    myList.insert(&item3);
    myList.insert(&item1);

    myList.print();

    myList.remove(1);

    std::cout << "==============================" << std::endl;

    myList.print();

    return 0;
}