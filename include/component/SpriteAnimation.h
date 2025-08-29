#ifndef G_AS_SPRITE_ANIMATION_H
#define G_AS_SPRITE_ANIMATION_H
#include "Sprite.h"
class SpriteAnimation : public Sprite
{
public:
    static SpriteAnimation* AddSpriteChild(ScreenObject* parent,const std::string& filePath,float scale);
    virtual void Update(float dt) override;
    virtual void SetTexture(const Texture& texture) override;

    int GetCurrentFrame() const { return m_currentFrame; }
    void SetCurrentFrame(int currentFrame) { m_currentFrame = currentFrame; }
    int GetTotalFrame() const { return m_totalFrame; }
    void SetTotalFrame(int totalFrame) { m_totalFrame = totalFrame; }
    int GetFps() const { return m_fps; }
    void SetFps(int fps) { m_fps = fps; }
    float GetFrameTimer() const { return m_frameTimer; }
    void SetFrameTimer(float frameTimer) { m_frameTimer = frameTimer; }
private:
    int     m_currentFrame = 0;
    int     m_totalFrame = 0;
    int     m_fps = 10;
    float   m_frameTimer = 0.0f;
};
#endif