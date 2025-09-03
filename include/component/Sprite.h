#ifndef G_AS_SPRITE_H
#define G_AS_SPRITE_H
#include "../core/ComponentObject.h"
#include <SDL3/SDL.h>
#include <string>
struct Texture
{
    SDL_Texture* texture = nullptr;
    SDL_FRect rect={0.0f,0.0f,0.0f,0.0f};
    float angle = 0.0f;
    bool isFlipped = false;
    Texture() = default;
    Texture(const std::string& path);
};

class Sprite : public ComponentObject
{
public:
    static Sprite* AddSpriteChild(ScreenObject* parent, const std::string& path,float scale,Anchor anchor = Anchor::Center);
    virtual void Render() override;

    Texture GetTexture() const;
    virtual void SetTexture(const Texture& texture);
    void SetFilp(bool flip);
    void SetAngle(float angle);
    bool GetFilp() const;
    float GetAngle() const;
    bool GetFinished() const;
    void SetFinished(bool finished);
protected:
    Texture m_texture;
    bool m_finished = false;
};

#endif