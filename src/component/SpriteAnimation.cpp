#include "component/SpriteAnimation.h"
SpriteAnimation *SpriteAnimation::AddSpriteChild(ScreenObject *parent, const std::string &filePath, float scale, Anchor anchor)
{
    auto ani = new SpriteAnimation();
    ani->Init();
    ani->SetTexture(Texture(filePath));
    ani->SetParent(parent);
    ani->SetScale(scale);
    ani->SetOffsetByAnchor(anchor);
    parent->AddChild(ani);
    return ani;
}
void SpriteAnimation::Update(float dt)
{
    m_frameTimer += dt;
    if(m_frameTimer >= 1.0f / m_fps)
    {
        m_frameTimer = 0.0f;
        m_currentFrame++;
        if(m_currentFrame >= m_totalFrame)
        {
            m_currentFrame = 0;
            if(!m_loop)
            {
                m_finished = true;
            }
        }
    }
    m_texture.rect.x = m_currentFrame * m_texture.rect.w;
}
void SpriteAnimation::SetTexture(const Texture &texture)
{
    m_texture = texture;
    m_totalFrame = (int)(m_texture.rect.w / m_texture.rect.h);
    m_texture.rect.w = m_texture.rect.h;
    m_size = glm::vec2(m_texture.rect.w,m_texture.rect.h);
}