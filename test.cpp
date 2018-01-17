//
// Created by benito on 1/5/18.
//

#include <ecs/Module.hpp>
#include <ecs/ASystem.hpp>
#include <ecs/Core.hpp>
#include <ecs/EntityFactory.hpp>
#include <Tcp/TcpManager.hpp>
#include <GameMgr/GameMgrSystem.hpp>

/* will receive std::string */
class System : public Sex::Module<System,
                                  std::string>
{
public:
    System(const std::shared_ptr<Sex::Mediator> &m) : Sex::Module<System, std::string>(m)
    {

    }

    void handle(const std::string& string)
    {
        std::cout << "I received " << string << std::endl;
    }
};


/* will receive int */
class Other : public Sex::Module<Other,
                                 int> /* template it on each type you want to receive */
{
public:
    Other(std::shared_ptr<Sex::Mediator> &m) : Sex::Module<Other, int>(m) {}

    void handle(int zizi)
    {
        std::cout << "I received " << zizi << std::endl;
    }
};


void test() {
    Sex::Core core; /* handle the main loop of the program */

    core.emplaceSystem<System>(); /* create the system System and save it */
    core.emplaceSystem<Other>(); /* Always prefere emplaceSystem if possible */


    Other &o = core.getSystem<Other>() /* retrieve a System with it's type */;
    std::string msg("Hello there");
    o.transmit(msg); /* transmit a message */
}

struct Nimoft : public Sex::Module<Nimoft,
        std::shared_ptr<Sex::GameObject>> /* template it on each type you want to receive */
{
    Nimoft(const std::shared_ptr<Sex::Mediator> &m) : Sex::Module<Nimoft,
                                            std::shared_ptr<Sex::GameObject>>(m) {}

    void handle(const std::shared_ptr<Sex::GameObject>& entity)
    {
        std::cout << "I received " << entity->getId() << std::endl;
    }
};


void test2()
{
    Sex::Core core; /* handle the main loop of the program */
    core.emplaceSystem<Other>(); /* Always prefere emplaceSystem if possible */
    Other &o = core.getSystem<Other>() /* retrieve a System with it's type */;
    core.emplaceSystem<Nimoft>();

    auto sex = o.createObject<Sex::GameObject>();
    //auto sox = o.createObject<int>(); /* Doesn't work */

}

void test_main()
{
    Sex::Core core;

    core.emplaceSystem<rtype::mainServ::TcpManager>();
    core.emplaceSystem<mainServer::GameMgrSystem>();

    core.go();
}

int main(int ac, char **av)
{
    //test2();
    test_main();
}

    //rtype::client::UdpNetworkManager x;