#ifndef G_AS_COMPONENT_OBJECT_H
#define G_AS_COMPONENT_OBJECT_H
#include "ScreenObject.h"

class ComponentObject : public SDL_Object
{
public:
    //getter and setter
    ScreenObject* GetParent() const { return m_parent; }
    void SetParent(ScreenObject* parent) { m_parent = parent; }
    glm::vec2 GetOffset() const { return m_offset; }
    void SetOffset(const glm::vec2& offset) { m_offset = offset; }
    glm::vec2 GetSize() const { return m_size; }
    void SetSize(const glm::vec2& size) { m_size = size; }
protected:
    ScreenObject*       m_parent = nullptr; // 父对象
    glm::vec2           m_offset = glm::vec2(0.0f,0.0f); //相对于父对象坐标的偏移
    glm::vec2           m_size = glm::vec2(0.0f,0.0f); // 大小
};
#endif