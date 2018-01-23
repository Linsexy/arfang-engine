//
// Created by benito on 1/4/18.
//

#ifndef ECS_GAMEOBJECT_HPP
#define ECS_GAMEOBJECT_HPP

#include <unordered_map>
#include <memory>
#include <functional>
#include "ecs/Components/IComponent.hpp"
#include "utils/IndexType.hpp"

//Stands for "entities" in a ECS design pattern

namespace Sex {
    class GameObject {
    public:
		struct DeleteEvent
		{
			std::shared_ptr<GameObject> const &objectToDestroy;
			DeleteEvent(std::shared_ptr<GameObject> const &obj) : objectToDestroy(obj) {}
		};

        struct Loader
        {
            std::function<std::shared_ptr<GameObject>()> load;
            utils::IndexType::meta                       type;
        };


        static unsigned int __id__;

        GameObject(); /* GameObjects should only be created by the createObject function */
        GameObject(unsigned int);

        ~GameObject() = default;

        template<typename CT, typename... Args>
        bool emplaceComponent(Args const &... args) noexcept {
            static_assert(std::is_base_of<IComponent, CT>::value,
                          "You have to attach components, not ponies.");

            return (_components.emplace(utils::IndexType::get<CT>(), std::make_shared<CT>(args...)).second);
        }

        template<typename CT>
        bool addComponent(CT &component) noexcept {
            static_assert(std::is_base_of<IComponent, CT>::value,
                          "You have to attach components, not ponies.");
            return (_components.emplace(utils::IndexType::get<CT>(), std::make_shared<CT>(component)).second);
        }

        template<typename CT>
        CT &getComponent() {
            static_assert(std::is_base_of<IComponent, CT>::value,
                          "You have to attach components, not ponies.");

            const auto &ptr = _components.at(utils::IndexType::get<CT>());
            return (static_cast<CT &>(*ptr));
        }

        template<typename CT>
        const CT &getComponent() const {
            static_assert(std::is_base_of<IComponent, CT>::value,
                          "You have to attach components, not ponies.");

            const auto &ptr = _components.at(utils::IndexType::get<CT>());
            return (static_cast<const CT &>(*ptr));
        }

        template<typename CT>
        bool hasComponent() const noexcept {
            return (_components.find(utils::IndexType::get<CT>()) != _components.end());
        }

        template<typename CT>
        void detachComponent() {
            auto it = _components.find(utils::IndexType::get<CT>());
            if (it == _components.end()) {
                throw (std::out_of_range("Component not in Entity"));
            }
            _components.erase(it);
        }

        unsigned int getId() const;

    private:
        std::unordered_map<utils::IndexType::meta, std::shared_ptr<IComponent>> _components;
        unsigned int _id;
    };
}

#endif //ECS_GAMEOBJECT_HPP
