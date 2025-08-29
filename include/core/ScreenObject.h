#ifndef G_AS_SCREEN_OBJECT_H
#define G_AS_SCREEN_OBJECT_H
#include "Object.h"

class ScreenObject : public SDL_Object
{
public:
    ScreenObject() = default;
    virtual ~ScreenObject() = default;
    glm::vec2 GetRenderPos() const;
    virtual void SetRenderPos(const glm::vec2& pos);
protected:
    glm::vec2   m_renderPos = glm::vec2(0.0f);
};

#endif