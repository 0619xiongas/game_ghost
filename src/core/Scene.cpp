#include "core/Scene.h"
#include "core/GameEngine.h"
#include <algorithm>

void Scene::OnEvent(void *event)
{
    SDL_Object::OnEvent(event);
    for(auto& child : m_worldObjects)
    {
        if(child->IsActive())
        {
            child->OnEvent(event);
        }
    }
    for(auto& child : m_screenObjects)
    {
        if(child->IsActive())
        {
            child->OnEvent(event);
        }
    }
}

void Scene::Update(float dt)
{
    SDL_Object::Update(dt);
    for(auto& child : m_worldObjects)
    {
        if(child->IsActive())
        {
            child->Update(dt);
        }
    }
    for(auto& child : m_screenObjects)
    {
        if(child->IsActive())
        {
            child->Update(dt);
        }
    }
}

void Scene::Render()
{
    SDL_Object::Render();
    for(auto& child : m_worldObjects)
    {
        if(child->IsActive())
        {
            child->Render();
        }
    }
    for(auto& child : m_screenObjects)
    {
        if(child->IsActive())
        {
            child->Render();
        }
    }
}

void Scene::Clean()
{
    SDL_Object::Clean();
    for(auto& child : m_worldObjects)
    {
        child->Clean();
    }
    for(auto& child : m_screenObjects)
    {
        child->Clean();
    }
    m_worldObjects.clear();
    m_screenObjects.clear();
}
glm::vec2 Scene::WorldToScreenPos(const glm::vec2 &worldPos)
{
    return worldPos - m_camera_pos;
}

glm::vec2 Scene::ScreenToWorldPos(const glm::vec2 &screenPos)
{
    return screenPos + m_camera_pos;
}

glm::vec2 Scene::GetWorldSize() const
{
    return m_worldSize;
}
void Scene::SetWorldSize(const glm::vec2 &worldSize)
{
    m_worldSize = worldSize;
}

glm::vec2 Scene::GetCameraPos() const
{
    return m_camera_pos;
}

void Scene::SetCameraPos(const glm::vec2 &cameraPos)
{
    m_camera_pos = cameraPos;
    m_camera_pos = glm::clamp(m_camera_pos, glm::vec2(-5.0f), m_worldSize - glm::vec2(g_GameEngine->GetScreenSize()));
}
void Scene::AddChild(SDL_Object *child)
{
    if(child)
    {
        if(child->GetType() == ObjectType::OT_WorldObject)
        {
            m_worldObjects.push_back((WorldObject*)child);
        }
        else if(child->GetType() == ObjectType::OT_ScreenObject)
        {
            m_screenObjects.push_back((ScreenObject*)child);
        }
        else
        {
            m_childrens.push_back(child);
        }
    }
}

void Scene::RemoveChild(SDL_Object *child)
{
    if(child)
    {
        if(child->GetType() == ObjectType::OT_WorldObject)
        {
            m_worldObjects.erase(std::remove(m_worldObjects.begin(), m_worldObjects.end(), (WorldObject*)child), m_worldObjects.end());
        }
        else if(child->GetType() == ObjectType::OT_ScreenObject)
        {
            m_screenObjects.erase(std::remove(m_screenObjects.begin(), m_screenObjects.end(), (ScreenObject*)child), m_screenObjects.end());
        }
        else
        {
            m_childrens.erase(std::remove(m_childrens.begin(), m_childrens.end(), child), m_childrens.end());
        }
    }
}