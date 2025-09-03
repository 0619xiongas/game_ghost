#include "entity/Enemy.h"
#include "entity/Player.h"
#include "GameMacro.h"
#include "component/Collider.h"
void Enemy::Init()
{
    GameObject::Init();
    m_animNormal = SpriteAnimation::AddSpriteChild(this,"../assets/sprite/ghost-Sheet.png",2.0f);
    m_animHurt = SpriteAnimation::AddSpriteChild(this,"../assets/sprite/ghostHurt-Sheet.png",2.0f);
    m_animDead = SpriteAnimation::AddSpriteChild(this,"../assets/sprite/ghostDead-Sheet.png",2.0f);
    m_curAnim = m_animNormal;
    m_animDead->SetActive(false);
    m_animHurt->SetActive(false);
    m_animDead->SetLoop(false);
    m_maxSpeed = G_GAME_ENEMY_MAX_SPEED;
    m_collider = Collider::AddColliderChild(this, m_curAnim->GetSize() / 2.0f, Collider::ColliderType::Circle);
    m_attribute = Attribute::AddAttributeChild(this, 200.0f, 200.0f, 100.0f, 100.0f, 10.0f, 10.0f);
}

void Enemy::Update(float dt)
{
    GameObject::Update(dt);
    FollowTarget(m_target);
    Move(dt);
    m_tempTimer += dt;
    if(m_tempTimer >= 1.0f && m_tempTimer < 2.0f)
    {
        changeState(State::Hurt);
    }
    else if(m_tempTimer >= 2.0f)
    {
        changeState(State::Dead);
    }
    checkState();
    Attack();
}

void Enemy::FollowTarget(Player *target)
{
    if(!target) return ;
    auto dir = target->GetWorldPos() - GetWorldPos();
    dir = glm::normalize(dir);
    m_velocity = dir * m_maxSpeed;
}

void Enemy::changeState(State state)
{
    if(m_state == state) return;
    m_curAnim->SetActive(false);
    switch (state)
    {
    case State::Normal:
        m_curAnim = m_animNormal;
        break;
    case State::Hurt:
        m_curAnim = m_animHurt;
        break;
    case State::Dead:
        m_curAnim = m_animDead;
        break;
    default:
        break;
    }
    m_curAnim->SetActive(true);
    m_state = state;
}

void Enemy::checkState()
{
    if(m_state == State::Dead && m_animDead->GetFinished())
    {
        m_remove = true;
    }
}
void Enemy::Attack()
{
    if(!m_target) return;
    // 测试碰撞
    if(!m_collider || !m_target->GetCollider()) return;
    if(m_collider->IsCollide(m_target->GetCollider()))
    {
        // 打印日志信息 加上时间 秒
        SDL_Log("Enemy Attack, %llu",SDL_GetTicks());
    }
}
