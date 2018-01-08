//
// Created by benito on 1/8/18.
//

#ifndef RTYPE_CORE_HPP
#define RTYPE_CORE_HPP

/* Core class of the engine */
#include <memory>
#include "Mediator.hpp"

namespace Sex {
    class Core {
    private:
        std::unique_ptr<Mediator> mediator;
    public:

        template<typename ST, typename... Args>
        void addSystem(Args &... args) {
            static_assert(std::is_base_of<ASystem, ST>::value,
                          "addSystem function should be called with a type inheriting from ASystem");

            //ASystem::create<ST>(args...)
            auto s = std::make_shared<ST>(mediator.get(), args...);
            _systems.emplace(utils::IndexType::get<ST>(), s);
            mediator->addSystem(static_cast<ASystem *>(s.get()));
        }
        Mediator *getMediator() const
        {
            return (mediator.get());
        }

    private:
        std::unordered_map<unsigned int, std::shared_ptr<ASystem>> _systems;
    };
}

#endif //RTYPE_CORE_HPP
