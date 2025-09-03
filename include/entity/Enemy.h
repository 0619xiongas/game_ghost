#ifndef G_AS_ENEMY_H
#define G_AS_ENEMY_H
#include "core/GameObject.h"
#include "component/SpriteAnimation.h"
class Player;
class Enemy : public GameObject
{
    enum class State
    {
        Normal,
        Hurt,
        Dead
    };
public:
    Enemy() = default;
    ~Enemy() = default;
    void Init() override;
    void Update(float dt) override;

    Player* GetTarget() const { return m_target; }
    void SetTarget(Player* target) { m_target = target; }
    void FollowTarget(Player* target);
    void changeState(State state);
    void checkState();
    void Attack();

private:
    Player* m_target = nullptr; // 目标
    State m_state = State::Normal;
    SpriteAnimation* m_animNormal = nullptr;
    SpriteAnimation* m_animHurt = nullptr;
    SpriteAnimation* m_animDead = nullptr;
    SpriteAnimation* m_curAnim = nullptr;
    float m_tempTimer = 0.0f;
};
#endif