#ifndef G_AS_GAME_OBJECT_H
#define G_AS_GAME_OBJECT_H
#include "WorldObject.h"

class GameObject : public WorldObject
{
public:
    GameObject() = default;
    virtual ~GameObject() = default;
    glm::vec2 GetVelocity() const;
    void SetVelocity(const glm::vec2& vel);
    float GetMaxSpeed() const;
    void SetMaxSpeed(float maxSpeed);
    void Move(float dt);
protected:
    glm::vec2           m_velocity = glm::vec2(0.0f,0.0f);// 速度
    float               m_maxSpeed = 0.0f; // 最大速度
};

#endif