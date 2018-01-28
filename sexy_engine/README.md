# SexyEngine

The SexyEngine is an implementation of the ECS design pattern. For those who don't know about it, I'm going to cover it quickly. For others [click here](https://gitlab.com/farnir/rtype/edit/master/sexy_engine/README.md#how-to-use-entities-and-components).

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
In the SexyEngine, they all must inherit from IComponent.

##### How to use Entities and Components

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

### Systems

The third and last part composing the ECS pattern are Systems. Those hold the logic of your game (or whatever you're building), which means that they interact with entities
and their components, they're the *controllers* of your software. To give you an idea about their uses, people typically implement Systems such as Graphic, Physics, etc...

### Mediator and Systems

As I said, the Systems control interact with entities. In the SexyEngine i've chose to use an other design pattern, the Mediator. I'm not going to explain anything about it, because
it's one of the most used patterns and if you don't know about it, you can easily find informations about it and on the collaboratives internets.
Let's go back to our purpose. So systems can interacts with Entities, but also with other Systems (that's why I talked about Mediator).
To permit this, all the Systems MUST inherit from the [Module](include/ecs/Module.hpp) class, which itself inherit from [ASystem](include/ecs/ASystem.hpp).
All the systems contains a pointer to a [Mediator](include/ecs/Mediator.hpp) which allows them to communicate informations to others, using their *Module* interface.

**Systems are allowed to choose which information from other Systems they're interested in**. To do this, when inheriting from Module,
which is a templated class, you must give first, as template parameters, yourself (if this confuses you, see [this](https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern))
and then the *types* your want to receive. You must then provide an *handle* function for any type you *registered* to.

##### Exemple of Systems

```cpp

/* will receive std::string */
class System : public Sex::Module<System,
                                    std::string>
{
public:
    System(const std::shared_ptr<Sex::Mediator> &m) 
    : Sex::Module<System, std::string>(m)
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
    Other(std::shared_ptr<Sex::Mediator> const& m) : Sex::Module<Other, 
                                                                    int>(m) {}

    void handle(int lol)
    {
        std::cout << "I received " << lol << std::endl;
    }
};
```
### The core
The core class purpose if basically to control your controllers (the systems). It is itself a System, but containing others and calling periodically their *update* virtual method

```cpp
virtual void update(double) noexcept
```

This method goal is to allow systems to do internal work. The parameter represent the elapsed time since the last call in milliseconds. (more information in the Core documentation)

##### How to use Systems' communication

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

##### How to create Entities (GameObjects)

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