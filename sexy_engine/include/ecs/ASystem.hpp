//
// Created by benito on 1/4/18.
//

#ifndef PROJECT_ASYSTEM_HPP
#define PROJECT_ASYSTEM_HPP

#include <memory>
#include <iostream>
#include <functional>
#include <utils/IndexType.hpp>
#include "GameObject.hpp"

namespace Sex {
    class Mediator;

    class ASystem {

    protected:
        struct AbstractData /* Is useful to provide an interface in order to call virtual functions */
        {
            AbstractData(unsigned int d) : mType(d) {}
            unsigned int mType;
        };

        template <typename DT>
        struct ConcreteData : public AbstractData
        {
            ConcreteData(const DT& d)  : AbstractData(utils::IndexType::get<DT>()), data(d) {}
            DT data;
        };


    public:
        ASystem(const std::shared_ptr<Mediator> m = nullptr) : mediator(m)
        {}
        virtual void update() {};

        virtual ~ASystem() = default;

        Mediator *getMediator() const {return mediator.get();}

    protected:
        virtual void handler(const AbstractData& data) = 0;

    public:
        template <typename DT>
        void receive(const DT& data)
        {
            //std::cout << "start receiving" << std::endl;
            auto d = ConcreteData<DT>(data);
            this->handler(d);
        }

    protected:
        std::shared_ptr<Mediator> mediator;
    };
}
#endif //PROJECT_ASYSTEM_HPP
