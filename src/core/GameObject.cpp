#include "GameObject.h"
#include "GameEngine.h"
#include "Scene.h"
glm::vec2 GameObject::GetVelocity() const
{
    return m_velocity;
}

void GameObject::SetVelocity(const glm::vec2& vel)
{
    m_velocity = vel;
}

float GameObject::GetMaxSpeed() const
{
    return m_maxSpeed;
}

void GameObject::SetMaxSpeed(float maxSpeed)
{
    m_maxSpeed = maxSpeed;
}

void GameObject::Move(float dt)
{
    SetWorldPos(m_worldPos + m_velocity * dt);
    m_worldPos = glm::clamp(m_worldPos, glm::vec2(-10.0f), g_GameEngine->GetCurScene()->GetWorldSize());
}
bool GameObject::IsAlive() const
{
    if(!m_attribute) return false;
    return m_attribute->IsAlive();
}
void GameObject::TakeDamage(float dmg)
{
    if(m_attribute)
    {
        m_attribute->TakeDamage(dmg);
    }
}
