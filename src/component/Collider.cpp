#include "component/Collider.h"
#include "GameMacro.h"
#include "core/GameEngine.h"
void Collider::Render()
{
#ifdef GAME_DEBUG
    ComponentObject::Render();
    auto pos = m_parent->GetRenderPos() + m_offset;
    g_GameEngine->RenderFillCircle(pos, m_size, 0.5f);
#endif
}

Collider *Collider::AddColliderChild(ScreenObject *parent, glm::vec2 size, ColliderType type, Anchor anchor)
{
    auto collider = new Collider();
    collider->Init();
    collider->SetParent(parent);
    collider->SetSize(size);
    collider->SetOffsetByAnchor(anchor);
    collider->SetCollideType(type);
    parent->AddChild(collider);
    return collider;
}

bool Collider::IsCollide(Collider *other)
{
    if(m_type == ColliderType::Circle && other->GetCollideType() == ColliderType::Circle)
    {
        auto p1 = m_parent->GetPosition() + m_offset + m_size / 2.0f;
        auto p2 = other->GetParent()->GetPosition() + other->GetOffset() + other->GetSize() / 2.0f;
        return glm::length(p1 - p2) < (m_size.x + other->GetSize().x) / 2.0f;
    }
    return false;
}
