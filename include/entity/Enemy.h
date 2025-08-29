#ifndef G_AS_ENEMY_H
#define G_AS_ENEMY_H
#include "core/GameObject.h"
#include "component/SpriteAnimation.h"

class Enemy : public GameObject
{
public:
    Enemy() = default;
    ~Enemy() = default;
};
#endif