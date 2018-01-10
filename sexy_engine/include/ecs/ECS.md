# ECS

### How to use Entities and Components

```cpp
int main()
{
    GameObject Mylan;
    Mylan.attachComponent<PosComponent>(17, 27); /* creates a PosComponent with 17, 27 as parameters */
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
class System : public utils::Module<System,
                                    std::string>
{
public:
    System(Sex::Mediator * m) : utils::Module<System, std::string>(m)
    {

    }

    void handle(const std::string& string)
    {
        std::cout << "I received " << string << std::endl;
    }
};


/* will receive int */
class Other : public utils::Module<Other,
                                   int> /* template it on each type you want to receive */
{
public:
    Other(Sex::Mediator *m) : utils::Module<Other, int>(m) {}

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

    Other& o = core.getSystem<Other>() /* retrieve a System with it's type */;
    std::string msg("Hello there");
    o.transmit(msg); /* transmit a message */
}
```