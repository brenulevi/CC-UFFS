#include "List.h"

#include<iostream>

List::List() {
    first = NULL;
    last = NULL;
    size = 0;
}

// Verify if already exists
Item* List::searchItem(int id) {
    Item* aux;
    for(aux = first; aux != NULL; aux = aux->next) {
        if (aux->id == id) { return aux; }
    }
    return NULL;
}

// Add item to list
void List::insert(Item* item) {
    if(size == 0) {
        first = item;
        last = item;
        size++;
        return;
    }
    if(searchItem(item->id) != NULL) {
        std::cout << "Item com id ja existente." << std::endl;
        return;
    }
    Item* aux;
    for(aux = first; aux != NULL; aux = aux->next) {
        if(aux->id >= item->id) {
            if(aux == first) {
                aux->prev = item;
                item->next = aux;
                first = item;
                return;
            }
            item->next = aux;
            item->prev = aux->prev;
            aux->prev->next = item;
            aux->prev = item;
            return;
        }
    }
    item->prev = last;
    last->next = item;
    last = item;
    size++;
}

// Remove item from list
// a (b) c
void List::remove(int id) {
    if(id == 0) {
        Item* item = first;
        Item* aux = item;
        item->next->prev = NULL;
        first = item->next;
        return;
    }
    Item* aux;
    for(aux = first; aux != NULL; aux = aux->next) {
        if(aux->id == id) {
            Item* aux2 = aux;
            aux2->next->prev = aux->prev;
            aux2->prev->next = aux->next;
            free(aux2);
            return;
        }
    }
}

// Show elements in list
void List::print() {
    Item* aux;
    for(aux = first; aux != NULL; aux = aux->next) {
        std::cout << "Value: " << aux->id << std::endl;
    }
}
