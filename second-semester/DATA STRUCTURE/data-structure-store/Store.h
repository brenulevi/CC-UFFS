#pragma once

#include<string>
#include "List.h"

class Store {
public:
    bool exit;
    std::string name;

    List items;

    void Initialize(std::string _name);

    void Dashboard();

    void EasterEgg();
};