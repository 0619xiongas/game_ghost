#ifndef G_AS_COLLIDER_H
#define G_AS_COLLIDER_H
#include "../core/ComponentObject.h"

class Collider : public ComponentObject
{
public:
    enum class ColliderType
    {
        Box,
        Circle,
    };
    Collider() = default;
    ~Collider() = default;

    virtual void Render() override;
    static Collider* AddColliderChild(ScreenObject* parent, glm::vec2 size, ColliderType type,Anchor anchor = Anchor::Center);
    bool IsCollide(Collider* other);
    ColliderType GetCollideType()const{return m_type;}
    void SetCollideType(ColliderType type){m_type = type;}
protected:
    ColliderType m_type = ColliderType::Circle;
};
#endif