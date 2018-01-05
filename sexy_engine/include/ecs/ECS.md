# ECS

### How to use it

```cpp
int main()
{
    GameObject Mylan;

    Mylan.attachComponent<PosComponent>(17, 27);
    auto const& pos = Mylan.getComponent<PosComponent>();

    std::cout << pos.x << std::endl;
}
```