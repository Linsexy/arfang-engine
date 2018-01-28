# SexyEngine

The SexyEngine is an implementation of the ECS design pattern. For those who don't know about it, I'm gonna cover it quickly. For others [click here](https://gitlab.com/farnir/rtype/edit/master/sexy_engine/README.md#how-to-use-entities-and-components).

## ECS

First of all, the acronym means Entity Component System. It's a pattern that is commonly used in video games development due to it's modularity and ease to write/understand.
Let's start explanations with Entities.

### Entities

Basically, entities are the "objects" of the world. By this I mean every thing that can be seen (it's not mandatory), but mot generally, everything that compose
the game. In most of the implemantations, an Entity is only and ID and a bunch of Components (I explain it just after this). In the SexyEngine, the class representing it are [GameObjects](include/ecs/GAMEOBJECT.md).
In the SexyEngine, all your Entities are GameObjects (by inheritance or simply raw GameObjects).

### Components

I said it earlier, Entities are *composed* by [Components](nimoft). In fact, you can see Entities like a container of components, with an interface to interact with them, and an ID
in order to recognize them. The components are the data of GameObjects.

### How to use Entities and Components

```cpp
struct PosComponent : public IComponent
{
    unsigned int x;
    unsigned int y;
}


int main()
{
    GameObject Mylan; /* never create GameObjects like this (example below) */
    Mylan.emplaceComponent<PosComponent>(17, 27); /* creates a PosComponent with 17, 27 as parameters */
    if (Mylan.hasComponent<PosComponent>()) {
        auto const &pos = Mylan.getComponent<PosComponent>();
        std::cout << pos.x << std::endl;
    }
}
```

##### Every system needs to inherit from Module templated on the System itself.
##### The other template parameters represent all the types it wants to receive.

```cpp

/* will receive std::string */
class System : public Sex::Module<System,
                                    std::string>
{
public:
    System(Sex::Mediator * m) : Sex::Module<System, std::string>(m)
    {}

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
    Other(Sex::Mediator *m) : Sex::Module<Other, int>(m) {}

    void handle(int zizi)
    {
        std::cout << "I received " << zizi << std::endl;
    }
};

```
### How to use Systems

```cpp
int main()
{
    Sex::Core core; /* handle the main loop of the program */

    core.emplaceSystem<System>(); /* create the system System and save it */
    core.emplaceSystem<Other>(); /* Always prefere emplaceSystem if possible */
    //core.emplaceSystem<std::string> /* doesn't work */

    Other& o = core.getSystem<Other>() /* retrieve a System with it's type */;
    std::string msg("Hello there");
    o.transmit(msg); /* transmit a message */
}
```

### How to create Entities (GameObjects)

```cpp
struct Nimoft : public Sex::Module<Nimoft,
        std::shared_ptr<Sex::GameObject>> /* template it on each type you want to receive */
{
    Nimoft(Sex::Mediator *m) : Sex::Module<Nimoft,
                                            std::shared_ptr<Sex::GameObject>>(m) {}

    void handle(const std::shared_ptr<Sex::GameObject>& entity)
    {
        std::cout << "I received " << entity->getId() << std::endl;
    }
};

core.emplaceSystem<Nimoft>();

auto sex = o.createObject<Sex::GameObject>(); /* Only way to create Entities */
                                              /* First template argument is it's type, and others it's constructor's arguments */
//auto sox = o.createObject<int>(); /* Doesn't work */

```