#ifndef G_AS_WORLD_OBJECT_H
#define G_AS_WORLD_OBJECT_H
#include "ScreenObject.h"
class Collider;
class WorldObject : public ScreenObject
{
public:
    WorldObject() = default;
    virtual ~WorldObject() = default;
    virtual void Update(float dt) override;
    glm::vec2 GetWorldPos() const;
    void SetWorldPos(const glm::vec2& pos);
    virtual void SetRenderPos(const glm::vec2& pos) override;
    virtual glm::vec2 GetPosition() override{return GetWorldPos();}
    Collider* GetCollider(){return m_collider;}
    void SetCollider(Collider* collider){m_collider = collider;}
protected:
    glm::vec2           m_worldPos = glm::vec2(0.0f);
    Collider*           m_collider = nullptr;
};
#endif