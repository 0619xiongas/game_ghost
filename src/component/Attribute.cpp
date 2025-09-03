#include "component/Attribute.h"
#include "core/GameObject.h"
Attribute *Attribute::AddAttributeChild(GameObject *parent, float hp, float mHp, float mp, float mMp, float dmg, float reMp)
{
    Attribute* attribute = new Attribute();
    attribute->SetParent(parent);
    attribute->SetHp(hp);
    attribute->SetMaxHp(mHp);
    attribute->SetMp(mp);
    attribute->SetMaxMp(mMp);
    attribute->SetDmg(dmg);
    attribute->SetMpRecover(reMp);
    parent->AddChild(attribute);
    return attribute;
}
bool Attribute::TryUseMana(float mp)
{
    if(m_mp >= mp)
    {
        m_mp -= mp;
        return true;
    }
    return false;
}

void Attribute::TakeDamage(float dmg)
{
    if(m_isInvincible)
    {
        return;
    }
    m_hp -= dmg;
    if(m_hp < 0)
    {
        m_hp = 0;
        m_isAlive = false;
    }
    m_isInvincible = true;
    m_invTimer = 0.0f; // 重置
}

void Attribute::Update(float dt)
{
    SDL_Object::Update(dt);
    RecoverMp(dt);
    if(m_isInvincible)
    {
        m_invTimer += dt;
        if(m_invTimer >= m_invTime)
        {
            m_isInvincible = false;
            m_invTimer = 0.0f;
        }
    }
}

void Attribute::RecoverMp(float dt)
{
    m_mp += dt * m_mpRecover;
    if(m_mp > m_maxMp)
    {
        m_mp = m_maxMp;
    }
}
