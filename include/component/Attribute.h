#ifndef G_AS_ATTRIBUTE_H
#define G_AS_ATTRIBUTE_H
#include "../core/Object.h"

class GameObject;
class Attribute : public SDL_Object
{
public:
    Attribute() = default;
    ~Attribute() = default;

    static Attribute* AddAttributeChild(GameObject* parent, float hp, float mHp,float mp,float mMp,float dmg,float reMp);
    bool TryUseMana(float mp);
    void TakeDamage(float dmg);
    void Update(float dt) override;


    //getter
    float GetHp() const{return m_hp;}
    float GetMaxHp() const{return m_maxHp;}
    float GetMp() const{return m_mp;}
    float GetMaxMp() const{return m_maxMp;}
    float GetDmg() const{return m_dmg;}
    float GetMpRecover() const{return m_mpRecover;}
    GameObject* GetParent() const{return m_parent;}
    bool IsInvincible() const{return m_isInvincible;}
    bool IsAlive() const{return m_isAlive;}

    //setter
    void SetHp(float hp){m_hp = hp;}
    void SetMaxHp(float maxHp){m_maxHp = maxHp;}
    void SetMp(float mp){m_mp = mp;}
    void SetMaxMp(float maxMp){m_maxMp = maxMp;}
    void SetDmg(float dmg){m_dmg = dmg;}
    void SetMpRecover(float mpRecover){m_mpRecover = mpRecover;}
    void SetInvincible(bool invincible){m_isInvincible = invincible;}
    void SetAlive(bool alive){m_isAlive = alive;}
    void SetParent(GameObject* parent){m_parent = parent;}
private:
    void RecoverMp(float dt);
private:
    GameObject* m_parent = nullptr;
    float m_hp = 200.0f;
    float m_maxHp = 200.0f;
    float m_mp = 100.0f;
    float m_maxMp = 100.0f;
    float m_dmg = 10.0f;
    float m_mpRecover = 5.0f;

    float m_invTime = 1.5f;
    float m_invTimer = 0.0f;
    bool m_isAlive = true;
    bool m_isInvincible = false;
};


#endif // G_AS_ATTRIBUTE_H