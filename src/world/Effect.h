#ifndef G_AS_EFFECT_H
#define G_AS_EFFECT_H
#include "../core/WorldObject.h"
#include "../component/SpriteAnimation.h"
#include <string>
class Effect : public WorldObject
{
public:
    virtual void Update(float dt) override;
    static Effect* AddEffectChild(SDL_Object* parent, const std::string& path, const glm::vec2& pos, float scale = 1.0f,WorldObject* create = nullptr);

    //get and set
    WorldObject* GetCreate() { return m_create; }
    void SetCreate(WorldObject* create) { m_create = create; }
    SpriteAnimation* GetAnim() { return m_anim; }
    void SetAnim(SpriteAnimation* anim) { m_anim = anim; }
private:
    void CheckFinished();
private:
    SpriteAnimation* m_anim = nullptr;
    WorldObject* m_create = nullptr;

};
#endif