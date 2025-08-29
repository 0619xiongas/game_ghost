#include "entity/Player.h"
#include "core/GameEngine.h"
#include "core/Scene.h"
#include "GameMacro.h"
void Player::Init()
{
    GameObject::Init();
    m_maxSpeed = G_GAME_PLAYER_MAX_SPEED;
    m_animIdle = SpriteAnimation::AddSpriteChild(this, "../assets/sprite/ghost-idle.png", 2.0f);
    m_animMove = SpriteAnimation::AddSpriteChild(this, "../assets/sprite/ghost-move.png", 2.0f);
    m_animMove->SetActive(false);
}

void Player::OnEvent(void *event)
{
    GameObject::OnEvent(event);
}

void Player::Update(float dt)
{
    GameObject::Update(dt);
    CheckKeyboardInput();
    CheckStatus();
    Move(dt);
    SyncCameraPosition();
}

void Player::Render()
{
    GameObject::Render();
}

void Player::Clean()
{
    GameObject::Clean();
}

void Player::CheckKeyboardInput()
{
    m_velocity *= 0.9f;
    auto state = SDL_GetKeyboardState(NULL);
    //加速系数
    float acceleration = 1.0f;
    if(state[SDL_SCANCODE_LSHIFT] || state[SDL_SCANCODE_RSHIFT])
    {
        acceleration = 2.0f;
    }
    if (state[SDL_SCANCODE_W])
    {
        m_velocity.y = -m_maxSpeed * acceleration;
    }
    if(state[SDL_SCANCODE_S])
    {
        m_velocity.y = m_maxSpeed * acceleration;
    }
    if(state[SDL_SCANCODE_A])
    {
        m_velocity.x = -m_maxSpeed * acceleration;
    }
    if(state[SDL_SCANCODE_D])
    {
        m_velocity.x = m_maxSpeed * acceleration;
    }
}

void Player::SyncCameraPosition()
{
    g_GameEngine->GetCurScene()->SetCameraPos(m_worldPos - 
        g_GameEngine->GetScreenSize() / 2.0f);
}

void Player::CheckStatus()
{
    // 设置翻转
    if(m_velocity.x < 0)
    {
        m_animIdle->SetFilp(true);
        m_animMove->SetFilp(true);
    }
    else
    {
        m_animIdle->SetFilp(false);
        m_animMove->SetFilp(false);
    }
    // 判断激活那个动画
    bool isNewMove = glm::length(m_velocity) > 0.1f;
    if(isNewMove != m_isMoving)
    {
        m_isMoving = isNewMove;
        SetState(isNewMove);
    }
}

void Player::SetState(bool isMove)
{
    if(isMove)
    {
        m_animIdle->SetActive(false);
        m_animMove->SetActive(true);
        m_animMove->SetCurrentFrame(m_animIdle->GetCurrentFrame());
        m_animMove->SetFrameTimer(m_animIdle->GetFrameTimer());
    }
    else
    {
        m_animIdle->SetActive(true);
        m_animMove->SetActive(false);
        m_animIdle->SetCurrentFrame(m_animMove->GetCurrentFrame());
        m_animIdle->SetFrameTimer(m_animMove->GetFrameTimer());
    }
}