//
// Created by benito on 1/4/18.
//

#ifndef ECS_MEDIATOR_HPP
#define ECS_MEDIATOR_HPP

#include <unordered_map>
#include "ASystem.hpp"
#include "IMediator.hpp"

class IMediator : public BaseMediator<IMediator>
{
public:
    template <typename ST, typename... Args>
    void addSystem(Args&... args)
    {
        static_assert(std::is_base_of<ASystem, ST>::value,
                      "addSystem function should be called with a type inheriting from ASystem");

        //ASystem::create<ST>(args...)
        _systems.emplace(utils::IndexType::get<ST>(), std::make_shared<ST>(this, args...));
    }

    template <typename ST, typename T>
    void transmit(const ST *sender, const T& transmit)
    {
        auto id = utils::IndexType::get<T>();
        for (auto& sys : _systems)
        {
            ST * s = static_cast<ST *>(sys.second.get());
            auto v = s->getTypes();
            if (sys != sender && std::find(v.begin(), v.end(), v) != v.end())
                s->handle(transmit);
        }
    };

private:
    std::unordered_map<unsigned int, std::shared_ptr<ASystem>> _systems;
};

#endif //ECS_MEDIATOR_HPP
