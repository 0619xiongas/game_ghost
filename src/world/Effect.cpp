#include "Effect.h"
#include "../core/GameEngine.h"
#include "../core/Scene.h"
void Effect::Update(float dt)
{
    WorldObject::Update(dt);
    CheckFinished();
}

Effect *Effect::AddEffectChild(SDL_Object *parent, const std::string &path, const glm::vec2 &pos, float scale, WorldObject *create)
{
    auto effect = new Effect();
    effect->Init();
    effect->m_anim = SpriteAnimation::AddSpriteChild(effect,path,scale);
    effect->m_anim->SetLoop(false);
    effect->SetWorldPos(pos);
    effect->SetCreate(create);
    if(parent) parent->AddChild(effect);
    return effect;
}

void Effect::CheckFinished()
{
    if(m_anim)
    {
        if(m_anim->GetFinished())
        {
            m_remove = true;
            if(m_create) g_GameEngine->GetCurScene()->AddChild(m_create);
        }
    }
}
