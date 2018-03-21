# GameObject

Explanations about it in the [ECS](/sexy_engine/README.md) "course".

## Constructor

```cpp
GameObject(); /* GameObjects should only be created by the createObject function (see Module doc) */
GameObject(unsigned int);
```
## Members

``` cpp
template<typename CT, typename... Args>
bool emplaceComponent(Args&&... args) noexcept
```
create a Component and attach it to the entity.
```cpp
template<typename CT>
CT &getComponent()
```
returns the component given in argument. throws std::out_of_range in failure.

``` cpp
 template<typename CT>
 bool hasComponent() const noexcept
```
Check if CT is attached to the entity.
``` cpp
template<typename CT>
void detachComponent() 
 ```
 Removes a component of the entity. Throws in case of failure.
 ```cpp
 unsigned int getId() const noexcept
 ```
 All entities have id's.
