# ECS

### How to use it

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