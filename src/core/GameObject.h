#ifndef G_AS_GAME_OBJECT_H
#define G_AS_GAME_OBJECT_H
#include "WorldObject.h"
#include "../component/Attribute.h"
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
    Attribute* GetAttribute() const{return m_attribute;}
    void SetAttribute(Attribute* attribute){m_attribute = attribute;}
    bool IsAlive() const;
    void TakeDamage(float dmg);
protected:
    glm::vec2           m_velocity = glm::vec2(0.0f,0.0f);// 速度
    float               m_maxSpeed = 0.0f; // 最大速度
    Attribute*          m_attribute = nullptr;
};

#endif