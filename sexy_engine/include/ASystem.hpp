//
// Created by benito on 1/4/18.
//

#ifndef PROJECT_ASYSTEM_HPP
#define PROJECT_ASYSTEM_HPP

#include <memory>
#include <iostream>

class Mediator;

class ASystem
{
public:
    virtual void update() { std::cout << "updating" << std::endl; };
private:
    Mediator* mediator;
};

#endif //PROJECT_ASYSTEM_HPP
