#include "component/Sprite.h"
#include "core/GameEngine.h"

Texture::Texture(const std::string& path)
{
    texture = g_GameEngine->GetAssetManager()->GetTexture(path);
    if (texture == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"Textrue Constructure error\n");
        return;
    }
    SDL_GetTextureSize(texture,&rect.w,&rect.h);
}

Sprite *Sprite::AddSpriteChild(ScreenObject *parent, const std::string &path, float scale, Anchor anchor)
{
    Sprite* sprite = new Sprite();
    sprite->Init();
    sprite->SetParent(parent);
    sprite->SetTexture(Texture(path));
    sprite->SetScale(scale);
    sprite->SetOffsetByAnchor(anchor);
    parent->AddChild(sprite);
    return sprite;
}

void Sprite::Render()
{
    if(!m_texture.texture) return;
    if(!m_parent) return;
    if(m_finished) return;
    auto pos = m_parent->GetRenderPos() + m_offset;
    g_GameEngine->RenderTexture(m_texture,pos,m_size);
}

Texture Sprite::GetTexture() const
{
    return m_texture;
}
void Sprite::SetTexture(const Texture &texture)
{
    m_texture = texture;
    m_size = glm::vec2(texture.rect.w,texture.rect.h);
}
void Sprite::SetFilp(bool flip)
{
    m_texture.isFlipped = flip;
}

void Sprite::SetAngle(float angle)
{
    m_texture.angle = angle;
}

bool Sprite::GetFilp() const
{
    return m_texture.isFlipped;
}

float Sprite::GetAngle() const
{
    return m_texture.angle;
}
bool Sprite::GetFinished() const
{
    return m_finished;
}
void Sprite::SetFinished(bool finished)
{
    m_finished = finished;
}
