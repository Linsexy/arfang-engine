//
// Created by benito on 1/4/18.
//

#ifndef PROJECT_ASYSTEM_HPP
#define PROJECT_ASYSTEM_HPP

#include <memory>
#include <iostream>

class IMediator;

class ASystem
{
public:
    ASystem(IMediator * m=nullptr) : mediator(m) {}

    virtual void update() {};

    virtual ~ASystem() = default;

    template <typename T>
    void transmit(const T& t)
    {
        mediator->transmit(this, t);
    }
    /*
    template <typename ST, typename... Args>
    static std::shared_ptr<ASystem> create(const Args&... args) noexcept
    {
        static_assert(std::is_base_of<ASystem, ST>::value,
                      "addSystem function should be called with a type inheriting from ASystem");

        return (std::shared_ptr<ASystem>(new ST(args...)));
    }
     */

private:
    IMediator* mediator;
};

#endif //PROJECT_ASYSTEM_HPP
