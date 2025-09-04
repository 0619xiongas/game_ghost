#include "Object.h"
#include <algorithm>
void SDL_Object::OnEvent(void *event)
{
    for(auto& child : m_childrens)
    {
        if(child->IsActive())
        {
            child->OnEvent(event);
        }
    }
}

void SDL_Object::Update(float dt)
{
    if(!m_addList.empty())
    {
        for(auto& child : m_addList)
        {
            m_childrens.push_back(child);
        }
        m_addList.clear();
    }
    for(auto itr = m_childrens.begin(); itr != m_childrens.end();)
    {
        auto child = *itr;
        if(child->GetRemove())
        {
            itr = m_childrens.erase(itr);
            child->Clean();
            delete child;
        }
        else
        {
            if(child->IsActive())
            {
                child->Update(dt);
            }
            itr++;
        }
    }
}

void SDL_Object::Render()
{
    for(auto& child : m_childrens)
    {
        if(child->IsActive())
        {
            child->Render();
        }
    }
}

void SDL_Object::Clean()
{
    for(auto& child : m_childrens)
    {
        child->Clean();
    }
    m_childrens.clear();
}

void SDL_Object::AddChild(SDL_Object *child)
{
    if(child)
    {
        m_childrens.push_back(child);
    }
}

void SDL_Object::RemoveChild(SDL_Object *child)
{
    if(child)
    {
        auto itr = std::find(m_childrens.begin(), m_childrens.end(), child);
        if(itr != m_childrens.end())
        {
            m_childrens.erase(itr);
        }
    }
}

ObjectType SDL_Object::GetType() const
{
    return m_type;
}

void SDL_Object::SetType(ObjectType type)
{
    m_type = type;
}

bool SDL_Object::IsActive() const
{
    return m_isActive;
}

void SDL_Object::SetActive(bool active)
{
    m_isActive = active;
}
bool SDL_Object::GetRemove() const
{
    return m_remove;
}
void SDL_Object::SetRemove(bool remove)
{
    m_remove = remove;
}

void SDL_Object::SafeAddChild(SDL_Object *child)
{
    if(child)
    {
        m_addList.push_back(child);
    }
}
