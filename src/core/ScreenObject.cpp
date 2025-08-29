#include "core/ScreenObject.h"

glm::vec2 ScreenObject::GetRenderPos() const
{
    return m_renderPos;
}
void ScreenObject::SetRenderPos(const glm::vec2& pos)
{
    m_renderPos = pos;
}