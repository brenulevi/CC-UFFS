#include "Store.h"

#include<iostream>
#include<string>

void Store::Initialize(std::string _name) {
    name = _name;
}

void Store::Dashboard() {
    std::cout << "========== Dashboard Test ==========" << std::endl;
    std::cout << "1 - Easter Egg" << std::endl;
    std::cout << "0 - Exit" << std::endl;
    int response;
    std::cin >> response;
    if(response == 0) { 
        exit = true;
        return;
    }
}

void Store::EasterEgg() {
    std::cout << "========== Easter Egg! ==========" << std::endl;
    std::cout << "Olá, eu sou o Breno!" << std::endl;
    std::cout << "0 - Back" << std::endl;
    int response;
    std::cin >> response;
    if(response == 0) {
        return Dashboard();
    }
}