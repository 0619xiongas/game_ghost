#include "core/WorldObject.h"
#include "core/Scene.h"
#include "core/GameEngine.h"
void WorldObject::Update(float dt)
{
    ScreenObject::Update(dt);
    m_renderPos = g_GameEngine->GetCurScene()->WorldToScreenPos(m_worldPos);
}

glm::vec2 WorldObject::GetWorldPos() const
{
    return m_worldPos;
}

void WorldObject::SetWorldPos(const glm::vec2 &pos)
{
    m_worldPos = pos;
    m_renderPos = g_GameEngine->GetCurScene()->WorldToScreenPos(m_worldPos);
}

void WorldObject::SetRenderPos(const glm::vec2 &pos)
{
    m_renderPos = pos;
    m_worldPos = g_GameEngine->GetCurScene()->ScreenToWorldPos(m_renderPos);
}
